#include "paths.hpp"

#include "common.hpp"

namespace libassert::detail {
    using path_components = std::vector<std::string>;

    LIBASSERT_ATTR_COLD
    path_components parse_path(const std::string_view path) {
        #if IS_WINDOWS
         constexpr std::string_view path_delim = "/\\";
        #else
         constexpr std::string_view path_delim = "/";
        #endif
        // Some cases to consider
        // projects/libassert/demo.cpp               projects   libassert  demo.cpp
        // /glibc-2.27/csu/../csu/libc-start.c  /  glibc-2.27 csu      libc-start.c
        // ./demo.exe                           .  demo.exe
        // ./../demo.exe                        .. demo.exe
        // ../x.hpp                             .. x.hpp
        // /foo/./x                                foo        x
        // /foo//x                                 f          x
        path_components parts;
        for(const std::string& part : split(path, path_delim)) {
            if(parts.empty()) {
                // first gets added no matter what
                parts.push_back(part);
            } else {
                if(part.empty()) {
                    // nop
                } else if(part == ".") {
                    // nop
                } else if(part == "..") {
                    // cases where we have unresolvable ..'s, e.g. ./../../demo.exe
                    if(parts.back() == "." || parts.back() == "..") {
                        parts.push_back(part);
                    } else {
                        parts.pop_back();
                    }
                } else {
                    parts.push_back(part);
                }
            }
        }
        LIBASSERT_PRIMITIVE_ASSERT(!parts.empty());
        LIBASSERT_PRIMITIVE_ASSERT(parts.back() != "." && parts.back() != "..");
        return parts;
    }

    LIBASSERT_ATTR_COLD
    void path_trie::insert(const path_components& path) {
        LIBASSERT_PRIMITIVE_ASSERT(path.back() == root);
        insert(path, (int)path.size() - 2);
    }

    LIBASSERT_ATTR_COLD
    path_components path_trie::disambiguate(const path_components& path) {
        path_components result;
        path_trie* current = this;
        LIBASSERT_PRIMITIVE_ASSERT(path.back() == root);
        result.push_back(current->root);
        for(size_t i = path.size() - 2; i >= 1; i--) {
            LIBASSERT_PRIMITIVE_ASSERT(current->downstream_branches >= 1);
            if(current->downstream_branches == 1) {
                break;
            }
            const std::string& component = path[i];
            LIBASSERT_PRIMITIVE_ASSERT(current->edges.count(component));
            current = current->edges.at(component).get();
            result.push_back(current->root);
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    LIBASSERT_ATTR_COLD
    void path_trie::insert(const path_components& path, int i) {
        if(i < 0) {
            return;
        }
        if(!edges.count(path[i])) {
            if(!edges.empty()) {
                downstream_branches++; // this is to deal with making leaves have count 1
            }
            edges.insert({path[i], std::make_unique<path_trie>(path[i])});
        }
        downstream_branches -= edges.at(path[i])->downstream_branches;
        edges.at(path[i])->insert(path, i - 1);
        downstream_branches += edges.at(path[i])->downstream_branches;
    }

    LIBASSERT_ATTR_COLD
    parsed_paths process_paths(const std::vector<std::string>& paths) {
        // raw full path -> components
        std::unordered_map<std::string, path_components> parsed_paths;
        // base file name -> path trie
        std::unordered_map<std::string, path_trie> tries;
        for(const auto& path : paths) {
            if(!parsed_paths.count(path)) {
                auto parsed_path = parse_path(path);
                auto& file_name = parsed_path.back();
                parsed_paths.insert({path, parsed_path});
                if(tries.count(file_name) == 0) {
                    tries.insert({file_name, path_trie(file_name)});
                }
                tries.at(file_name).insert(parsed_path);
            }
        }
        // raw full path -> minified path
        std::unordered_map<std::string, std::string> files;
        size_t longest_file_width = 0;
        for(auto& [raw, parsed_path] : parsed_paths) {
            const std::string new_path = join(tries.at(parsed_path.back()).disambiguate(parsed_path), "/");
            internal_verify(files.insert({raw, new_path}).second);
            if(new_path.size() > longest_file_width) {
                longest_file_width = new_path.size();
            }
        }
        return {files, std::min(longest_file_width, size_t(50))};
    }
}
