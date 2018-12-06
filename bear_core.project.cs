using BearBuildTool.Projects;
using System.IO;
using System;
public class bear_core :Project
{
	public bear_core(string ProjectPath)
	{
		PCHFile=Path.Combine(ProjectPath,"source","BearCore.cpp");
		PCHIncludeFile="BearCore.hpp";
		AddSourceFiles(Path.Combine(ProjectPath,"source"),true);
		Include.Public.Add(Path.Combine(ProjectPath,"include"));
		Projects.Private.Add("tinyxml");
        Projects.Private.Add("BugTrap");
    }
} 