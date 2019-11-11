##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=StrongholdEngine
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
Date                   :=11/11/2019
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :="C:/Program Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/bin/g++.exe"
SharedObjectLinkerName :="C:/Program Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/bin/g++.exe" -shared -fPIC
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
RcCompilerName         :="C:/Program Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/bin/windres.exe"
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)psapi 
ArLibs                 :=  "psapi" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := "C:/Program Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/bin/ar.exe" rcu
CXX      := "C:/Program Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/bin/g++.exe"
CC       := "C:/Program Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/bin/gcc.exe"
CXXFLAGS := -m32 -g -O0 -Wall -m32  $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall  $(Preprocessors)
ASFLAGS  := 
AS       := "C:/Program Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/bin/as.exe"


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=./build-$(ConfigurationName)//stats.cpp$(ObjectSuffix) ./build-$(ConfigurationName)//main.cpp$(ObjectSuffix) 



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
./build-$(ConfigurationName)//stats.cpp$(ObjectSuffix): stats.cpp ./build-$(ConfigurationName)//stats.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Moi/Documents/StrongholdEngine/StrongholdEngine/stats.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/stats.cpp$(ObjectSuffix) $(IncludePath)
./build-$(ConfigurationName)//stats.cpp$(DependSuffix): stats.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT./build-$(ConfigurationName)//stats.cpp$(ObjectSuffix) -MF./build-$(ConfigurationName)//stats.cpp$(DependSuffix) -MM stats.cpp

./build-$(ConfigurationName)//stats.cpp$(PreprocessSuffix): stats.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ./build-$(ConfigurationName)//stats.cpp$(PreprocessSuffix) stats.cpp

./build-$(ConfigurationName)//main.cpp$(ObjectSuffix): main.cpp ./build-$(ConfigurationName)//main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Moi/Documents/StrongholdEngine/StrongholdEngine/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
./build-$(ConfigurationName)//main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT./build-$(ConfigurationName)//main.cpp$(ObjectSuffix) -MF./build-$(ConfigurationName)//main.cpp$(DependSuffix) -MM main.cpp

./build-$(ConfigurationName)//main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ./build-$(ConfigurationName)//main.cpp$(PreprocessSuffix) main.cpp


-include ./build-$(ConfigurationName)///*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


