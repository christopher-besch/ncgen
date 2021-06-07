#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "global.h"

// I'd probably use some macros for this
const char* filename     = "default";
std::string version      = "0.0.1";
std::string content      = "";
std::string post_content = "";
bool        importTime   = false;

// explanitory comment needed
constexpr unsigned int strint(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (strint(str, h + 1) * 33) ^ str[h];
}

int main(int argc, char* argv[])
{
    console_log("-- NCGEN --");
    console_log("Version : " + version);
    console_log("Target : Python");

    if (argc < 2)
    {
        std::cerr << "Please specify the input file as the first cli parameter" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    filename = argv[1];
    console_log(filename);

    console_log("Starting generation process... \n");

    std::filesystem::path filepath                     = filename;
    std::string           filepathwithoutfileextension = (filepath.replace_extension()).string(); // Sorry for this horrible naming, I am tired

    std::ofstream writefile(filepathwithoutfileextension + ".py");

    std::ifstream file(filename);
    std::string   filestr;
    std::string   parameter = "";

    while (std::getline(file, filestr))
    {
        parameter = filestr.substr(filestr.find(" ") + 1);
        switch (strint((filestr.substr(0, filestr.find(" "))).data()))
        {
        case strint("printtext"):
            append_content("print('" + parameter + "')\n");
            break;

        case strint("printvar"):
            append_content("print(str(" + parameter + "))\n");
            break;

        case strint("compilelog"):
            console_log(parameter);
            break;

        case strint("//"):
            break;

        case strint("int"):
            append_content(parameter.substr(0, parameter.find(" ") + 3) + "int(" +
                           parameter.substr(parameter.find(" ") + 3) + ")\n");
            break;

        case strint("str"):
            append_content(parameter.substr(0, parameter.find(" ") + 3) + "str('" +
                           parameter.substr(parameter.find(" ") + 3) + "')\n");
            break;

        case strint("float"):
            append_content(parameter.substr(0, parameter.find(" ") + 3) + "float(" +
                           parameter.substr(parameter.find(" ") + 3) + ")\n");
            break;

        case strint("if"):
            append_content("if (" + parameter + "):\n");
            break;

        case strint("else"):
            append_content("else:\n");
            break;

        case strint(""):
            break;

        case strint("<indent>"):
            append_content("    ");
            break;

        case strint("endif"):
            break;

        case strint("[html]"):
            console_log("Ignoring export type HTML - not available for Python.");
            break;

            // PYTHON SPECIFIC

        case strint("py.sleep"):
            importTime = true;
            append_content("time.sleep(" + parameter + ")");
            break;

        // comments are badly needed
        default:
            if (filestr.substr(0, filestr.find(" ")).find("js") !=
                std::string::npos)
            {
                console_log("Ignoring JavaScript specific function: ");
                console_log("> " + filestr + "\n");
                break;
            }
            else
            {
                if (filestr.substr(0, filestr.find(" ")).find("html") !=
                    std::string::npos)
                {
                    console_log("Ignoring HTML specific function: ");
                    console_log("> " + filestr + "\n");
                    break;
                }
                else
                {
                    console_log("\nERROR : Unknown syntax :");
                    console_log("> " + filestr + "\n");
                    break;
                }
            }
        }
    }

    if (importTime)
    {
        console_log("Importing python dependency 'time'...");
        content.insert(0, "import time\n");
        console_log("Generation complete.");
        writefile << content;
    }
    else
    {
        console_log("Generation complete.");
        writefile << content;
    }
    // system("PAUSE");
    return 0;
}
