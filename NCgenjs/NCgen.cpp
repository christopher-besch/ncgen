#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "global.h"

const char* filename = "default";
std::string version = "0.0.1";
std::string content = "";
std::string post_content = "";
bool exportHtml = false;
bool exportHtmlIndex = false;

constexpr unsigned int strint(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (strint(str, h + 1) * 33) ^ str[h];
}

int main(int argc, char* argv[])
{
	console_log("-- NCGEN --");
	console_log("Version : " + version);
	console_log("Target : JavaScript");

	for (int i = 0; i < argc; ++i) {

		if (argv[i] != argv[0]) {
			filename = argv[i];
			console_log(filename);
		}
	}
	console_log("Starting generation process... \n");

	std::filesystem::path filepath = filename;
	std::string filepathwithoutfileextension = (filepath.replace_extension()).string(); //Sorry for this horrible naming, I am tired

	std::ifstream file(filename);
	std::string filestr;
	std::string parameter = "";

	while (std::getline(file, filestr)) {
		parameter = filestr.substr(filestr.find(" ") + 1);
		switch (strint((filestr.substr(0, filestr.find(" "))).data())) {

		case strint("printtext"):
			append_content("console.log('" + parameter + "');\n");
			break;

		case strint("printvar"):
			append_content("console.log(" + parameter + ");\n");
			break;

		case strint("compilelog"):
			console_log(parameter);
			break;

		case strint("//"):
			break;

		case strint("int"):
			append_content(parameter.substr(0, parameter.find(" ") + 3) + "" + parameter.substr(parameter.find(" ") + 3) + ";\n");
			break;

		case strint("str"):
			append_content(parameter.substr(0, parameter.find(" ") + 3) + "'" + parameter.substr(parameter.find(" ") + 3) + "';\n");
			break;

		case strint("float"):
			append_content(parameter.substr(0, parameter.find(" ") + 3) + "" + parameter.substr(parameter.find(" ") + 3) + ";\n");
			break;

		case strint("if"):
			append_content("if (" + parameter + ") {\n");
			break;

		case strint("else"):
			append_content("} else {\n");
			break;

		case strint(""):
			break;

		case strint("<indent>"):
			break;

		case strint("endif"):
			append_content("}\n");
			break;

		default:
			if (filestr.substr(0, filestr.find(" ")).find("py") != std::string::npos) {
				console_log("Ignoring Python specific function: ");
				console_log("> " + filestr + "\n");
				break;
			}
			else {
				console_log("\nERROR : Unknown syntax :");
				console_log("> " + filestr + "\n");
				break;
			}

			// JS SPECIFIC

		case strint("js.alerttext"):
			append_content("window.alert('" + parameter + "');\n");
			break;

		case strint("js.alertvar"):
			append_content("window.alert(" + parameter + ");\n");
			break;

		case strint("js.writedocument"):
			append_content("document.write(" + parameter + ");\n");
			break;

		case strint("[html]"):
			content.insert(0, "<html>\n<script>\n");
			exportHtml = true;
			break;

		case strint("[htmlindex]"):
			content.insert(0, "<html>\n<script>\n");
			exportHtml = true;
			exportHtmlIndex = true;
			break;

			// JS-HTML SPECIFIC

		case strint("html.addtag"):
			if (exportHtml) {
				append_content_post(parameter + "\n");
			}
			else {
				console_log("ERROR : You are trying to use HTML function but do not have HTML export enabled. Enable HTML export with [HTML] to activate HTML features.\n");
			}
		}
	}

	if (exportHtml) {
		append_content("</script>\n");
		apply_post_content();
		append_content("</html>\n");
		console_log("Generation complete.");
		if (!exportHtmlIndex) {
			std::ofstream writefile(filepathwithoutfileextension + ".html");
			writefile << content;
		}
		else {
			std::ofstream writefile("index.html");
			writefile << content;
		}
	}
	else {
		std::ofstream writefile(filepathwithoutfileextension + ".js");
		console_log("Generation complete.");
		writefile << content;
	}
	//system("PAUSE");
	return 0;
}