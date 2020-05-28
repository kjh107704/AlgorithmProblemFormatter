/*
    compile command: g++ -std=c++17 ./dist/jsoncpp.cpp main.cpp -lstdc++fs
    execute command: a.exe <문제 플랫폼> <문제 번호> <문제 제목> <파일 확장자>
*/
#include <iostream>
#include <fstream>
#include <set>
#include <experimental/filesystem>
#include "./dist/json/json.h"

std::string FIRST_LINE = "// Problem Information";

int EXTENSION_SIZE = 3;
std::string EXTENSION_LIST[] = {"cpp", "c", "py"};
std::set<std::string> extension(EXTENSION_LIST, EXTENSION_LIST + EXTENSION_SIZE);

int FORMAT_ORDER_SIZE = 7;
std::string FORMAT_ORDER[] = {"Platform", "Problem", "Title", "Algorithm", "Desc", "TryAgain", "isSolved"};

Json::Value getJsonObject(std::string fileName)
{
    Json::Value jsonObject;
    std::ifstream jsonFile(fileName, std::ifstream::binary);
    jsonFile >> jsonObject;

    return jsonObject;
}

Json::Value setJsonObject(Json::Value &format, Json::Value &platform, std::string target_platform, std::string target_problem, std::string target_title)
{
    format["Platform"] = platform[target_platform]["MainLink"];
    format["Problem"] = platform[target_platform]["ProblemLinkSuffix"].asString() + target_problem;
    format["Title"] = target_title;

    return format;
}

std::string getFilePath(Json::Value &platform, std::string target_platform, std::string target_problem, std::string target_extension)
{
    std::string path = platform[target_platform]["Path"].asString() + target_problem + "." + target_extension;

    return path;
}

void checkPathExists(std::string path)
{
    std::experimental::filesystem::path myPath = path;
    if (!(std::experimental::filesystem::exists(myPath)))
    {
        std::cout << path << " doesn't exists\n";
        if (std::experimental::filesystem::create_directories(myPath))
        {
            std::cout << "....Successfully Created !\n";
        }
    }
    return;
}

void removeFile(std::string path)
{
    std::experimental::filesystem::path filePath = path;
    if (std::experimental::filesystem::exists(filePath))
    {
        std::experimental::filesystem::remove(filePath);
    }
    return;
}

int main(int argc, char *argv[])
{
    Json::Value format = getJsonObject("Format.json");
    Json::Value platform = getJsonObject("Platform.json");

    if (argc < 4)
    {
        printf("ERROR: <문제 플랫폼> <문제 번호> <문제 제목> <파일 확장자> 를 모두 입력해야 합니다.");
        return -1;
    }

    std::string target_platform = argv[1];
    std::string target_problem = argv[2];
    std::string target_title = argv[3];
    std::string target_extension = argv[4];

    format = setJsonObject(format, platform, target_platform, target_problem, target_title);

    std::string targetFile_Path = getFilePath(platform, target_platform, target_problem, target_extension);
    std::string problemInformationFile_Path = "./tmp.txt";
    std::string resultFile_Path = "./result." + target_extension;

    checkPathExists(platform[target_platform]["Path"].asString());

    std::fstream targetFile;
    targetFile.open(targetFile_Path, std::ios::in | std::ios::out | std::ios::app);

    char firstLine_arr[100];
    targetFile.getline(firstLine_arr, 100);
    std::string firstLine = firstLine_arr;

    targetFile.close();

    if (firstLine != FIRST_LINE)
    {
        std::fstream problemInformationFile(problemInformationFile_Path, std::ios::in | std::ios::out | std::ios::trunc);
        std::fstream resultFile(resultFile_Path, std::ios::in | std::ios::out | std::ios::trunc);
        targetFile.open(targetFile_Path, std::ios::in | std::ios::out);

        if (problemInformationFile.is_open())
        {
            problemInformationFile << FIRST_LINE + "\n";
            problemInformationFile << "/*\n";
            for (int i = 0; i < FORMAT_ORDER_SIZE; i++)
                problemInformationFile << "\t" << FORMAT_ORDER[i] << " : \"" << format[FORMAT_ORDER[i]].asString() << "\"\n";
            problemInformationFile << "*/\n";

            if (targetFile.is_open() && resultFile.is_open())
            {
                problemInformationFile.seekg(0);
                resultFile.seekg(0);

                resultFile << problemInformationFile.rdbuf() << targetFile.rdbuf();

                resultFile.clear();
                resultFile.seekg(0);
                targetFile.clear();
                targetFile.seekg(0);

                targetFile << resultFile.rdbuf();
            }
            else
            {
                std::cout << "error2\n";
            }

            std::cout << "Successfully create file!\n"
                      << "Path: " << targetFile_Path << "\n";
        }
        else
        {
            std::cout << "error\n";
        }

        resultFile.close();
        targetFile.close();
        problemInformationFile.close();

        removeFile(resultFile_Path);
        removeFile(problemInformationFile_Path);
    }
    else
    {
        std::cout << "Ooops!! File already exists in proper format!\n"
                  << "Path: " << targetFile_Path << "\n";
    }
}