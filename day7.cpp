#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <ranges>
#include <map>
#include <algorithm>
#include <vector>
#include <stack>

std::string trim(std::string_view const in)
{
    auto view
        = in
        | std::views::drop_while(isspace)
        | std::views::reverse
        | std::views::drop_while(isspace)
        | std::views::reverse;
    return {view.begin(), view.end()};
}

struct Info {
	bool is_dir = false;
	std::string name = "";
	long size = 0;
	std::map<std::string, Info> items;
	Info* parent = nullptr;

	static Info CreateDirectory(const std::string& name, Info* parent) {
		Info result = Info { .is_dir = true, .name = name, .size = 0, .items = {}, .parent = parent };
		if (parent && !parent->items.contains(name)) {
			parent->items.emplace(name, result);
		}
		return result;
	}

	static Info CreateFile(const std::string& name, long size, Info* parent) {
		Info result = Info { .is_dir = false, .name = name, .size = size, .items = {}, .parent = parent };
		if (parent && !parent->items.contains(name)) {
			parent->items.emplace(name, result);
		}
		return result;
	}

	long GetSize() const {
		if (!is_dir) {
			return size;
		}
		else
		{
			long subtotal = 0;
			for (auto& [name, item] : items) {
				subtotal += item.GetSize();
			}
			return subtotal;
		}
	}
};

Info root = Info::CreateDirectory("/", nullptr);

std::string filename(const std::string& path)
{
	int index = path.find_last_of('/');
	return path.substr(index + 1);
}

std::string parent_path(const std::string& path)
{
	int index = path.find_last_of('/');
	if (index == 0) {
		return "/";
	}
	return path.substr(0, index);
}

std::string append_path(const std::string& parent, const std::string& path)
{
	std::string result = parent;

	if (!result.ends_with('/')) { result += '/';}
	
	result += path.substr(trim(path).find_first_not_of('/'));

	return result;
}

int main(int argc, char* argv[])
{
	std::ifstream file("day7_input.txt");


	std::string current = "/";
	Info* current_dir = &root;

	std::string line;
	while (std::getline(file, line)) {
		if (line.starts_with("$"))
		{
			std::string command =  line.substr(2);
			if (command.starts_with("cd"))
			{
				std::string dir = command.substr(3);
				if (dir.starts_with(".."))
				{
					current_dir = current_dir->parent;
					current = parent_path(current);
				}
				else if (dir.starts_with("/"))
				{
					current = "/";
					current_dir = &root;
				}
				else
				{
					current_dir = &current_dir->items.at(dir);
					current = append_path(current, dir);
				}
				std::cout << current << std::endl;
			}
		}
		else
		{
			if (line.starts_with("dir"))
			{
				std::string dir_name = line.substr(4);
				Info::CreateDirectory(dir_name, current_dir);
			}
			else
			{
				std::size_t index = line.find(' ');
				long size = std::strtol(line.c_str(), nullptr, 10);
				std::string file_name = line.substr(index + 1);
				Info::CreateFile(file_name, size, current_dir);
			}
		}
	}

	long availableSpace = 70000000;
	long usedSpace = root.GetSize();
	long freeSpace = availableSpace - usedSpace;
	long spaceNeeded = 30000000 - freeSpace;

	std::cout << usedSpace << std::endl;
	std::cout << spaceNeeded << std::endl;

	long sum = 0;
	long smallestRemovable = LONG_MAX;

	std::stack<Info> stack;
	stack.push(root);
	while (!stack.empty())
	{
		Info curr = stack.top();
		stack.pop();
		if (curr.is_dir)
		{
			for (auto& [_, item] : curr.items)
			{
				stack.push(item);
			}

			long currSize = curr.GetSize();
			if (currSize <= 100000) {
				sum += currSize;
			}

			if (currSize >= spaceNeeded && currSize < smallestRemovable)
			{
				smallestRemovable = currSize;
			}
		}
	}

	std::cout << "Part 1: " << sum << std::endl;
	std::cout << "Part 2: " << smallestRemovable << std::endl;

	return 0;
}