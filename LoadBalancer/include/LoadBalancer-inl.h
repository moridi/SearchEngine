#ifndef LOAD_BALANCER_INL_H_
#define LOAD_BALANCER_INL_H_

#ifndef LOAD_BALANCER_H_
#error "LoadBalancer-inl.h" should be included only in "LoadBalancer.h" file.
#endif

#include <bits/stdc++.h>

LoadBalancer::LoadBalancer() noexcept
{
}

std::string LoadBalancer::remove_spaces(std::string line) const
{
	constexpr char SPACE = ' ';

	std::string::iterator end_position = std::remove(line.begin(),
			line.end(), SPACE);
	line.erase(end_position, line.end());
	return line;
}

std::vector<std::string> LoadBalancer::tokenize(const std::string& line,
		const char delimiter) const noexcept
{
	std::vector<std::string> tokens;
	std::stringstream string_stream(line);
	std::string intermediate;
	while (getline(string_stream, intermediate, delimiter))
		tokens.push_back(remove_spaces(intermediate));

	return tokens;
}

bool LoadBalancer::is_new_file(std::string entry)
{
	constexpr char CURRENT_DIRECTORY[] = ".";
	constexpr char PARENT_DIRECTORY[] = "..";

	return entry != CURRENT_DIRECTORY && entry != PARENT_DIRECTORY;
}

std::string LoadBalancer::get_full_path(std::string entry)
{
	constexpr char CURRENT_DIRECTORY[] = ".";
	constexpr char SLASH[] = "/";

	char current_path[PATH_MAX + 1];
	realpath(CURRENT_DIRECTORY, current_path);

	return std::string(current_path) + SLASH + dataset_directory +
			SLASH + entry;
}

size_t LoadBalancer::get_size(std::string value)
{
	return value.size() * static_cast<size_t>(sizeof(char));
}

void LoadBalancer::set_argv_element(char*** argv, int index, std::string value)
{
	(*argv)[index] = reinterpret_cast<char*>(malloc(get_size(value)));
	strcpy((*argv)[index], value.c_str());
}

void LoadBalancer::set_file_arguments(char*** argv, int& index,
		const std::vector<std::string>& files_name)
{
	for (int j = 0; j < files_name.size(); ++index, ++j)
		set_argv_element(argv, index, files_name[j]);
}

void LoadBalancer::set_argv(const std::vector<std::string>& files_name,
		char*** argv)
{
	int index;
	set_filter_arguments(argv, index);
	set_file_arguments(argv, index, files_name);
	(*argv)[index] = nullptr;
}

std::string LoadBalancer::get_token(std::string line, const int index) const
{
	constexpr char ASSIGN_DELIMITER = '=';

	std::vector<std::string> tokens = tokenize(line, ASSIGN_DELIMITER);
	return tokens[index];
}

#endif
