#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
using namespace std;

string camelToScreamingSnakeCase(string camel);
void writeGetFuncDec(ofstream& file, string varType, string varName);
void writeSetFuncDec(ofstream& file, string varType, string varName);
void writeGetFuncDef(ofstream& file, string className, string varType, string varName);
void writeSetFuncDef(ofstream& file, string className, string varType, string varName);

int main(int argc, char* argv[])
{
    //this section gets the file path to the class data
    string classDataFilePath;
    string filePath = "";
    if (argc >= 2)
    {
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            filePath.push_back(argv[1][i]);
        }
        classDataFilePath = filePath;

        //removes file name from path
        size_t lastSlash = filePath.find_last_of("/\\");
        if (lastSlash == string::npos)
        {
            filePath = "./";
        }
        else
        {
            filePath.erase(lastSlash+1, filePath.size() - lastSlash);
        }
    }
    else
    {
        cerr << "Program not given proper arguments, use the following commandline argument" << endl;
        cerr << "./classMaker.exe classdata" << endl;
        cerr << "or simply open classdata with classMaker.exe by rightclicking and selecting open with, or dragging classdata onto classMaker.exe" << endl;
        return 1;
    }

    string className;
    //vector of type name pairs
    vector <pair<string,string>> varTypeName(0);
    //use these as temp variables to add to varTypeName
    string varType;
    string varName;

    //open sample data as a input file stream
    ifstream classData{classDataFilePath};
    classData >> className;

    //open header and definition files as output file streams
    ofstream classDeclarationFile{filePath + className + ".h"}  ;
    ofstream classDefinitionFile {filePath + className + ".cpp"};

    //setting up header's start
    classDeclarationFile << "#ifndef " << camelToScreamingSnakeCase(className + ".h") << endl;
    classDeclarationFile << "#define " << camelToScreamingSnakeCase(className + ".h") << endl << endl;

    //get #includes included in header
    classData >> varType;
    classData >> varName;
    while(varType == "#include")
    {
        classDeclarationFile << varType << " " << varName << endl;
        classData >> varType;
        classData >> varName;
    }
    classDeclarationFile << endl;

    //start class declaration
    classDeclarationFile << "class " << className << "{" << endl;
    classDeclarationFile << "private:" << endl;

    //setting up class definition's start
    classDefinitionFile << "#include \"" << className + ".h" << "\"" << endl << endl;

    //getting type name pairs
    while (!classData.eof())
    {
        varTypeName.push_back(make_pair(varType, varName));
        classData >> varType;
        classData >> varName;
    }
    if (varTypeName.at(varTypeName.size()-1).second != varName)
    varTypeName.push_back(make_pair(varType, varName));

    //declaring variables in private: section of class
    for (int i = 0; i < varTypeName.size(); i++)
    {
        classDeclarationFile << "\t" << varTypeName.at(i).first << " " << varTypeName.at(i).second << ";" << endl;
    }

    //declaring public functions in class
    classDeclarationFile << "public:" << endl;

    //declaring all values initializer function
    classDeclarationFile << "\t" << className << "(";
    for (int i = 0; i < varTypeName.size(); i++)
    {
        classDeclarationFile << varTypeName.at(i).first << " " << varTypeName.at(i).second;
        if (i != varTypeName.size()-1)
        {
            classDeclarationFile << ", ";
        }
        
    }
    classDeclarationFile << ");" << endl << endl;

    //defining all values initializer function
    classDefinitionFile << className << "::" << className << "(";
    for (int i = 0; i < varTypeName.size(); i++)
    {
        classDefinitionFile << varTypeName.at(i).first << " " << varTypeName.at(i).second;
        if (i != varTypeName.size() - 1)
        {
            classDefinitionFile << ", ";
        }
    }
    classDefinitionFile << "){" << endl;
    for (int i = 0; i < varTypeName.size(); i++)
    {
        classDefinitionFile << "\tthis->" << varTypeName.at(i).second << " = " << varTypeName.at(i).second << ";" << endl;
    }
    classDefinitionFile << "}" << endl << endl;

    //declaring getters and setters in class
    for (int i = 0; i < varTypeName.size(); i++)
    {
        writeGetFuncDec(classDeclarationFile, varTypeName.at(i).first, varTypeName.at(i).second);
        writeSetFuncDec(classDeclarationFile, varTypeName.at(i).first, varTypeName.at(i).second);
        classDeclarationFile << endl;
    }

    //defining getters and setters in definition file
    for (int i = 0; i < varTypeName.size(); i++)
    {
        writeGetFuncDef(classDefinitionFile, className, varTypeName.at(i).first, varTypeName.at(i).second);
        writeSetFuncDef(classDefinitionFile, className, varTypeName.at(i).first, varTypeName.at(i).second);
        classDefinitionFile << endl;
    }

    //ending header file stuff
    classDeclarationFile << "};" << endl;
    classDeclarationFile << "#endif";
    

    return 0;
}

void writeGetFuncDec(ofstream& file, string varType, string varName)
{
    string upperCaseVarName = varName;
    upperCaseVarName.at(0) = toupper(upperCaseVarName.at(0));

    file << "\t" << varType << " Get" << upperCaseVarName << "();" << endl;
}
void writeSetFuncDec(ofstream& file, string varType, string varName)
{
    string upperCaseVarName = varName;
    upperCaseVarName.at(0) = toupper(upperCaseVarName.at(0));

    file << "\tvoid Set" << upperCaseVarName << "(" << varType << " " << varName << ");" << endl;
}
void writeGetFuncDef(ofstream& file, string className, string varType, string varName)
{
    string upperCaseVarName = varName;
    upperCaseVarName.at(0) = toupper(upperCaseVarName.at(0));

    file << varType << " " << className << "::Get" << upperCaseVarName << "(){" << endl;
    file << "\treturn " << varName << ";" << endl;
    file << "}" << endl;
}
void writeSetFuncDef(ofstream& file, string className, string varType, string varName)
{
    string upperCaseVarName = varName;
    upperCaseVarName.at(0) = toupper(upperCaseVarName.at(0));

    file << "void " << className << "::Set" << upperCaseVarName << "(" << varType << " " << varName << "){" << endl;
    file << "\tthis->" << varName << " = " << varName << ";" << endl;
    file << "}" << endl;
}
string camelToScreamingSnakeCase(string camel)
{
    string snake = "";
    for (int i = 0; i < camel.size(); i++)
    {
        char iterChar = camel.at(i);
        
        if (iterChar == '.')
        iterChar = '_';

        if (isupper(iterChar) && i!=0)
        {
            snake.push_back('_');
        }

        snake.push_back(toupper(iterChar));
    }
    return snake;
}