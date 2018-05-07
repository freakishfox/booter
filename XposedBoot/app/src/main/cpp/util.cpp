//
// Created by dfzhang on 2018/4/19.
//

#include "util.h"
#include "Comm.h"

unsigned long get_module_base(pid_t pid, const char *module_name){

    //1. open /proc/pid/maps
    char maps_name[20] = {0};
    sprintf(maps_name, "/proc/%d/maps", pid);

    FILE *f = fopen(maps_name, "r");
    if(!f){
        return 0;
    }

    //2. read content
    while(!feof(f)){
        char map_item[1024] = {0};
        fgets(map_item, sizeof(map_item), f);

        //40053000-40058000 r-xp 00000000 b3:19 1442       /system/bin/app_process.

        //3. remove some space
        std::string rs_map_item = remove_repeated_space(map_item);
        memset(map_item, 0, 1024);
        sprintf(map_item, "%s", rs_map_item.c_str());

        std::vector<std::string> vec_rs = split_string(map_item, "\x20");
        if(vec_rs.size() != 6){
            continue;
        }

        std::string module_name_found = vec_rs[5];
        if(!strstr(module_name_found.c_str(), module_name)){
            continue;
        }

        //3. only module contains execute attribute is our target
        std::string module_attr_found = vec_rs[1];
        if(!strstr(module_attr_found.c_str(), "x")){
            continue;
        }

        std::string str_load_addr = vec_rs[0];
        int start_addr = 0, end_addr = 0;
        sscanf(str_load_addr.c_str(), "%x-%x", &start_addr, &end_addr);

        fclose(f);
        return (unsigned long)start_addr;
    }

    fclose(f);
    return 0;
}


std::vector<std::string> split_string(char *src, const char *delmiter){
    std::vector<std::string> vec_rs;

    char *tmp = strtok(src, delmiter);
    while(tmp){
        vec_rs.push_back(std::string(tmp));

        tmp = strtok(NULL, delmiter);
    }

    return vec_rs;
}

std::string remove_repeated_space(std::string src) {

    bool is_prev_space = false;
    for (std::string::iterator itr = src.begin(); itr != src.end();) {
        if (*itr != '\x20') {
            is_prev_space = false;

            itr++;
            continue;
        }

        if (is_prev_space) {

            itr = src.erase(itr);
            continue;
        }
        else {
            is_prev_space = true;
        }

        itr++;
    }

    return src;
}

std::string bytes_to_hex(char *src, size_t size){

    std::string rs;
    for(int idx = 0; idx < size; idx ++){
        char szTxt[4] = {0};
        sprintf(szTxt, "%02x", src[idx]);

        rs.append(szTxt);
    }

    return rs;
}