#ifndef __DC_CONFIG_H__
#define __DC_CONFIG_H__

#include <sstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

class dc_config : public boost::enable_shared_from_this<dc_config>
{
public:
	typedef boost::shared_ptr<dc_config> pointer;

	static pointer Create(std::string path)
	{
		return pointer(new dc_config(path));
	}

	std::string GetString(std::string name)
	{
		return pt2.get<std::string>(name); 
	}

	void SetString(std::string name, std::string value)
	{
		pt2.put(name, value);
	}

	int GetInteger(std::string name)
	{
		return pt2.get<int>(name);
	}

	void SetInteger(std::string name, int value)
	{
		pt2.put(name, value);
	}

	void Save(std::string path)
	{
		std::ostringstream buf;
		write_json(buf, pt2, true);
		
		std::ofstream ofs(path);
		ofs << buf.str();
		ofs.close();
	}

private:
	dc_config(std::string path)
	{
		std::ifstream t(path);
		std::string json;

		t.seekg(0, std::ios::end);
		json.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		json.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

		std::istringstream is(json);
		read_json(is, pt2);

		t.close();
	}

	ptree pt2;
};

#endif 
