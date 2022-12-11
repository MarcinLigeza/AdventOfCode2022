#include <iostream>
#include <algorithm>
#include <memory>
#include <map>

#include "../utils.h"

using namespace std;

class File
{
public:
    File(string _name, uint64_t _size) : name(_name), size(_size) {}

    friend bool operator==(const File & f1, const File & f2);

    string get_name() const { return name; };
    uint64_t get_size() const { return size; }; 

private:
    string name;
    uint64_t size;
};

class Directory
{
public:
    Directory(const string & _name, Directory * const _parent) : 
    name(_name), parent(_parent)
     {}

    void add_file(const string & name, uint64_t size)
    {
        if(0 == std::count_if(files.begin(), files.end(), [&name](File f)
                { return f.get_name() == name; }))
        {
            files.emplace_back(name, size);
        }
    }

    void add_directory(const string & name)
    {
        if(0 == std::count_if(dirs.begin(), dirs.end(), [&name](Directory d)
                { return d.name == name; }))
        {
            dirs.emplace_back(name, this);
        }
    }

    Directory * get_parent() { return parent; }
    Directory * get_child(const string & name)
    {
        auto child = find_if(dirs.begin(), dirs.end(), [&name](Directory d)
        {
            return d.name == name;
        });
        if (child == dirs.end())
        {
            cout << "ERROR: could not find dir named: " << name << endl;
            return nullptr;
        }
        return child.base();
    }

    string get_name() const { return name; }

    uint64_t get_size() const
    {
        cout << "Dir: " << name << ":" << endl;
        uint64_t size{0ULL};
        for (const auto & file : files)
        {
            size += file.get_size();
            cout << " - file - " << file.get_name() << ", " << file.get_size() << endl; 
        }

        for (const auto & dir : dirs)
        {
            size += dir.get_size();
            cout << " - dir - " << dir.get_name() << endl;
        }
        return size;
    }
    
    uint64_t get_size_of_dirs_with_maximal_size(uint64_t max_size, uint64_t & result) const
    {
        uint64_t size{0ULL};
        for (const auto & file : files)
        {
            size += file.get_size();
        }

        for (const auto & dir : dirs)
        {
            auto dir_size = dir.get_size_of_dirs_with_maximal_size(max_size, result);
            size += dir_size;
            if(dir_size <= max_size)
            {
                result += dir_size;
            }
        }
        return size;
    }

    uint64_t calculate_dir_size_map(map<uint64_t, string>& map) const
    {
        uint64_t size{0ULL};
        for (const auto & file : files)
        {
            size += file.get_size();
        }

        for (const auto & dir : dirs)
        {
            auto dir_size = dir.calculate_dir_size_map(map);
            size += dir_size;
            map.emplace(dir_size, dir.get_name());
        }
        return size;
    }

    friend bool operator== (const Directory & d1, const Directory & d2);

private:
    string name;
    vector<Directory> dirs;
    vector<File> files;
    Directory* const parent;
};

bool operator== (const Directory & d1, const Directory & d2)
{
    return d1.name == d2.name;
}

bool operator==(const File & f1, const File & f2)
{
    return f1.name == f2.name;
}

class FileSystem
{
public:
    FileSystem() : root("/", nullptr)
    {
        current_dir = &root;
    }

    void parse_input(const shared_ptr<vector<string>>& _data)
    {
        data = _data;
        current_line = data->begin();

        while(current_line != data->end())
        {
            if(current_line->at(0) == '$')
            {
                parse_command();
            }
        }
    }

    uint64_t get_size()
    {
        return root.get_size();
    }

    uint64_t get_size_of_dirs_with_maximal_size(uint64_t max_size)
    {
        uint64_t result = 0ULL;
        root.get_size_of_dirs_with_maximal_size(max_size, result);
        return result;
    }

    void calculate_dir_size_map()
    {
        auto root_size = root.calculate_dir_size_map(dir_size_map);
        dir_size_map.emplace(root_size, root.get_name());
    }

    void show_candidate_to_delete()
    {
        auto taken_space = root.get_size();
        auto free_space = 70000000 - taken_space;

        auto needed_space = 30000000 - free_space;

        cout << "taken space: " << taken_space << " free_space: " << free_space
             << " needed_space: " << needed_space << endl;

        for(const auto & dir : dir_size_map)
        {
            cout << dir.second << ": " << dir.first;
            if(dir.first > needed_space)
            {
                cout << " - you can pick this one" << endl;
            }
        }
    }

private:
    void parse_command()
    {
        if(current_line->substr(0, 4) == "$ cd")
        {
            parse_cd_command();
        }
        else if (current_line->substr(0,4) == "$ ls")
        {
            parse_ls_command();
        }
    }

    void parse_cd_command()
    {
        if(current_line->substr(5, 1) == "/")
        {
            current_dir = &root;
        }
        else if(current_line->substr(5) == "..")
        {
            current_dir = current_dir->get_parent();
        }
        else
        {
            auto dir_name = current_line->substr(5);
            change_dir(dir_name);
        }
        ++current_line; // TODO: check where incrementation should be done
    }

    void parse_ls_command()
    {
        while(increment_current_line() && (current_line->at(0) != '$'))
        {
            if(current_line->at(0) == 'd')
            {
                auto dir_name = current_line->substr(4);
                current_dir->add_directory(dir_name);
            }
            else
            {
                auto space_pos = current_line->find_first_of(' ');
                auto file_size = stoi(current_line->substr(0, space_pos));
                auto file_name = current_line->substr(space_pos+1);
                current_dir->add_file(file_name, file_size);
            }
        }

    }

    void change_dir(string name)
    {
        auto new_dir = current_dir->get_child(name);
        if(new_dir)
        {
            current_dir = new_dir;
        }
        else
        {
            cout << "ERROR: current dir: " << current_dir->get_name()
                 << " does not have child dir: " << name << ". Throwing exception" << endl;
            throw(std::runtime_error("Parsing error"));
        }
    }

    bool increment_current_line()
    {
        if((++current_line) != data->end())
        {
            return true;
        }
        return false;
    }

    Directory root;
    Directory * current_dir;

    shared_ptr<vector<string>> data;
    vector<string>::const_iterator current_line;
    map<uint64_t, string> dir_size_map{};
};

int main()
{
    auto data = make_shared<vector<string>>(load_data("data.txt"));

    FileSystem file_system;
    file_system.parse_input(data);

    cout << file_system.get_size() << endl;
    cout << file_system.get_size_of_dirs_with_maximal_size(100000) << endl;
    file_system.calculate_dir_size_map();
    file_system.show_candidate_to_delete();


}