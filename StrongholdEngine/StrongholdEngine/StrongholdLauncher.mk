##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=StrongholdLauncher
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=C:/Users/Moi/Documents/StrongholdEngine/StrongholdEngine
ProjectPath            :=C:/Users/Moi/Documents/StrongholdEngine/StrongholdEngine
IntermediateDirectory  :=./build-$(ConfigurationName)/
OutDir                 :=./build-$(ConfigurationName)/
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Moi
Date                   :=10/11/2019
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/MinGW/bin/g++.exe
SharedObjectLinkerName :=C:/MinGW/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=.\build-$(ConfigurationName)\bin\$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/MinGW/bin/ar.exe rcu
CXX      := C:/MinGW/bin/g++.exe
CC       := C:/MinGW/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall -std=c++11 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=./build-$(ConfigurationName)//launcher_injector_injector.c$(ObjectSuffix) ./build-$(ConfigurationName)//launcher_main.cpp$(ObjectSuffix) ./build-$(ConfigurationName)//launcher_Launcher.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ./build-$(ConfigurationName)//.d $(Objects) 
	@if not exist ".\build-$(ConfigurationName)\" mkdir ".\build-$(ConfigurationName)\"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist ".\build-$(ConfigurationName)\" mkdir ".\build-$(ConfigurationName)\"
	@if not exist "".\build-$(ConfigurationName)\bin"" mkdir "".\build-$(ConfigurationName)\bin""

./build-$(ConfigurationName)//.d:
	@if not exist ".\build-$(ConfigurationName)\" mkdir ".\build-$(ConfigurationName)\"

PreBuild:


##
## Objects
##
./build-$(ConfigurationName)//launcher_injector_injector.c$(ObjectSuffix): launcher/injector/injector.c ./build-$(ConfigurationName)//launcher_injector_injector.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Moi/Documents/StrongholdEngine/StrongholdEngine/launcher/injector/injector.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/launcher_injector_injector.c$(ObjectSuffix) $(IncludePath)
./build-$(ConfigurationName)//launcher_injector_injector.c$(DependSuffix): launcher/injector/injector.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT./build-$(ConfigurationName)//launcher_injector_injector.c$(ObjectSuffix) -MF./build-$(ConfigurationName)//launcher_injector_injector.c$(DependSuffix) -MM launcher/injector/injector.c

./build-$(ConfigurationName)//launcher_injector_injector.c$(PreprocessSuffix): launcher/injector/injector.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ./build-$(ConfigurationName)//launcher_injector_injector.c$(PreprocessSuffix) launcher/injector/injector.c

./build-$(ConfigurationName)//launcher_main.cpp$(ObjectSuffix): launcher/main.cpp ./build-$(ConfigurationName)//launcher_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Moi/Documents/StrongholdEngine/StrongholdEngine/launcher/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/launcher_main.cpp$(ObjectSuffix) $(IncludePath)
./build-$(ConfigurationName)//launcher_main.cpp$(DependSuffix): launcher/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT./build-$(ConfigurationName)//launcher_main.cpp$(ObjectSuffix) -MF./build-$(ConfigurationName)//launcher_main.cpp$(DependSuffix) -MM launcher/main.cpp

./build-$(ConfigurationName)//launcher_main.cpp$(PreprocessSuffix): launcher/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ./build-$(ConfigurationName)//launcher_main.cpp$(PreprocessSuffix) launcher/main.cpp

./build-$(ConfigurationName)//launcher_Launcher.cpp$(ObjectSuffix): launcher/Launcher.cpp ./build-$(ConfigurationName)//launcher_Launcher.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Moi/Documents/StrongholdEngine/StrongholdEngine/launcher/Launcher.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/launcher_Launcher.cpp$(ObjectSuffix) $(IncludePath)
./build-$(ConfigurationName)//launcher_Launcher.cpp$(DependSuffix): launcher/Launcher.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT./build-$(ConfigurationName)//launcher_Launcher.cpp$(ObjectSuffix) -MF./build-$(ConfigurationName)//launcher_Launcher.cpp$(DependSuffix) -MM launcher/Launcher.cpp

./build-$(ConfigurationName)//launcher_Launcher.cpp$(PreprocessSuffix): launcher/Launcher.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ./build-$(ConfigurationName)//launcher_Launcher.cpp$(PreprocessSuffix) launcher/Launcher.cpp


-include ./build-$(ConfigurationName)///*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


