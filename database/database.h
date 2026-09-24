#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
namespace database {
std::string databasedir = "database/";
class ParseCONFIG {
    public:
    char terminator = '\n';
    std::string configfile = "database/txt.db";

    std::vector<std::string> readfiles() {
        std::string filecontent{};
        std::string collector{};
        std::vector<std::string> filenames{};
        std::ifstream cfgfile(configfile);
        if (!cfgfile) {
            std::cout << "error reading config file!\n";
            return {};
        }
        std::stringstream cache{};
        cache << cfgfile.rdbuf();
        filecontent = cache.str();
        cfgfile.close();
        for (const char content : filecontent) {
            if (content == terminator) {
                collector = databasedir + collector;
                filenames.push_back(collector);
                collector.clear();
            } else {
                collector += content;
            }
        }
        collector = databasedir + collector;
        filenames.push_back(collector);
        return filenames;
    }
};
class ParseTXT {
    public:
    char group_begin = '[';
    char group_end = ']';
    char text_ident = '\"';
    char terminator = '\n';
    char comment_ident = ';';
    bool lastErr{};
    struct Chef {
        bool group_statement{};
        bool text_statement{};
        bool comment{};
    };
    struct Output {
        std::string title{};
        std::vector<std::string> texts;
    };
    Chef _chef{};
    Output _sout{};
    std::vector<Output> _out{};

    void reset_sout() {
        _sout.texts.clear();
        _sout.title.clear();
    }
    void parseFile(const std::string file) {
        bool last_was_string{};
        Output _sout_cp{};
        std::string tmpcollector{};
        for (const char content : file) {
            // Processor
            if (_chef.group_statement) {
                if (content == group_end) {
                    _chef.group_statement = false;
                    _sout.title = tmpcollector;
                    tmpcollector.clear();
                    continue;
                }
                tmpcollector += content;
            }
            if (_chef.text_statement) {
                if (content == text_ident) {
                    _chef.text_statement = false;
                    _sout.texts.push_back(tmpcollector);
                    tmpcollector.clear();
                    _out.push_back(_sout);
                    _sout_cp = _sout;
                    reset_sout();
                    continue;
                }
                if (content == terminator) {
                    _sout.texts.push_back(tmpcollector);
                    tmpcollector.clear();
                    continue;
                }
                tmpcollector += content;
            }
            if (_chef.comment) {
                if (content == terminator) {
                    _chef.comment = false;
                    continue;
                }
            }
            // Handler
            if (content == group_begin) {
                _chef.group_statement = true;
                last_was_string = false;
                continue;
            }
            if (content == text_ident) {
                if (last_was_string) {
                    _sout = _sout_cp;
                    _out.pop_back();
                    _chef.text_statement = true;
                    continue;
                }
                last_was_string = true;
                _chef.text_statement = true;
                continue;
            }
            if (content == comment_ident) {
                _chef.comment = true;
                continue;
            }
            // When nothing (will be another string statement)
        }
        _chef.group_statement = false;
        _chef.text_statement = false;
        _chef.comment = false;
        reset_sout();
    }
    // getByTitle: return vector of strings with all text segments
    std::vector<std::string> getByTitle(std::string title) {
        lastErr = false;
        for (int i = 0; i < _out.size(); i++) {
            if (_out.at(i).title == title) {
                return _out.at(i).texts;
            }
        }
        lastErr = true;
        return {};
    }
    // getSizeOfTitle: return size of title text segments
    size_t getSizeOfTitle(std::string title) {
        return getByTitle(title).size();
    }
    // getText: get a specif text segement of a title, else last line 
    std::string getText(std::string title, int where) {
        std::vector<std::string> texts = getByTitle(title);
        if (lastErr) {
            std::cout << "title " << title << "doesnt exist!\n";
            return "";
        }
        lastErr = false;
        if (where >= getSizeOfTitle(title)) {
            std::cout << "requested text segment " << where << " in " << title << " is invalid, returning last element\n";
            lastErr = true;
            return texts.at(getSizeOfTitle(title) - 1);
        }
        return texts.at(where);
    }
    // confirmTitle: returns given title if exists, raises lastErr if not exists
    const std::string confirmTitle(std::string title) {
        bool found{};
        lastErr = false;
        std::string gtitle = title;
        std::vector<std::string> allTitles = getTitles();
        for (int i = 0; i < allTitles.size(); i++) {
            if (gtitle == allTitles.at(i)) {
                found = true;
                break;
            }
        }
        if (!found) {
            lastErr = true;
            return "";
        }
        return gtitle;
    }
    // getTitle: return vector of all loaded titles
    std::vector<std::string> getTitles() {
        std::vector<std::string> allTitles{};
        for (int i = 0; i < _out.size(); i++) {
            allTitles.push_back(_out.at(i).title);
        }
        return allTitles;
    }
    // visualizeText: print text segments from int x -> int y
    void visualizeText(std::string title, int from, int to) {
        for (from; from < to; from++) {
            std::string text = getText(title, from);
            if (!lastErr) {
                std::cout << text << "\n";
            } else {
                std::cout << "visualizing title " << title << " failed, non-existing!\n";
                return;
            }
        }
        lastErr = false;
    }
    // handleOnLastErr: executes a given callback when last operation was unsuccsessful
    void handleOnLastErr(std::function<void()> handler) {
        if (lastErr) {
            handler();
        }
    }

};


}