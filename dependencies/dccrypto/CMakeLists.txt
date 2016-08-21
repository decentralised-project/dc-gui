cmake_minimum_required (VERSION 3.0)

project ( dccrypto )

find_package( Boost COMPONENTS system date_time signals )
find_package( OpenSSL )

set( EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build" )
set( LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build" )

set( ROOT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

set  ( ROOT_HEADERS      
       "include/crypt_network_manager.hpp"
       "include/crypt_ec_helper.hpp"
     )

set  ( ROOT_SRC
       "src/crypt_network_manager.cpp"
       "src/crypt_ec_helper.cpp"
     )

source_group( "include" FILES ${ROOT_HEADERS} )
source_group( "src" FILES ${ROOT_SRC} )

include_directories( ${ROOT_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} "${CMAKE_SOURCE_DIR}/dependencies/dcp2p/include" )

link_directories( 
	${Boost_LIBRARY_DIRS}
)

ADD_LIBRARY( dccrypto STATIC ${ROOT_HEADERS} ${ROOT_SRC} )

SET_TARGET_PROPERTIES( dccrypto PROPERTIES LIBRARY_OUTPUT_NAME dccrypto ARCHIVE_OUTPUT_NAME dccrypto )

if ( MSVC )
	ADD_DEFINITIONS( 
		-D_WIN32_WINNT=0x0501
	)
    set_target_properties( dccrypto PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/libs)
    set_target_properties( dccrypto PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/libs)
    set_target_properties( dccrypto PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/libs)
endif ( MSVC )