##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=first_server
ConfigurationName      :=Debug
WorkspacePath          := "C:\study\c++"
ProjectPath            := "C:\study\c++\first_server"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Alpha
Date                   :=28/05/2016
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :="C:/Program Files (x86)/mingw-w64/i686-5.1.0-posix-dwarf-rt_v4-rev0/mingw32/bin/g++.exe"
SharedObjectLinkerName :="C:/Program Files (x86)/mingw-w64/i686-5.1.0-posix-dwarf-rt_v4-rev0/mingw32/bin/g++.exe" -shared -fPIC
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="first_server.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :="C:/Program Files (x86)/mingw-w64/i686-5.1.0-posix-dwarf-rt_v4-rev0/mingw32/bin/windres.exe"
LinkOptions            :=  -lws2_32 -llibxml2
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)C:/xmllibs/libxml2-2.7.8.win32/include $(IncludeSwitch)C:/xmllibs/iconv-1.9.2.win32/include $(IncludeSwitch)C:/study/c/code/sqlite3 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)sqlite3 
ArLibs                 :=  "libsqlite3.a" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)C:/xmllibs/libxml2-2.7.8.win32/lib $(LibraryPathSwitch)C:/study/c/code/sqlite3/bin/Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := "C:/Program Files (x86)/mingw-w64/i686-5.1.0-posix-dwarf-rt_v4-rev0/mingw32/bin/ar.exe" rcu
CXX      := "C:/Program Files (x86)/mingw-w64/i686-5.1.0-posix-dwarf-rt_v4-rev0/mingw32/bin/g++.exe"
CC       := "C:/Program Files (x86)/mingw-w64/i686-5.1.0-posix-dwarf-rt_v4-rev0/mingw32/bin/gcc.exe"
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := "C:/Program Files (x86)/mingw-w64/i686-5.1.0-posix-dwarf-rt_v4-rev0/mingw32/bin/as.exe"


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/socket_win.c$(ObjectSuffix) $(IntermediateDirectory)/struct_to_json.c$(ObjectSuffix) $(IntermediateDirectory)/list.c$(ObjectSuffix) $(IntermediateDirectory)/xml.c$(ObjectSuffix) $(IntermediateDirectory)/db_manager.c$(ObjectSuffix) $(IntermediateDirectory)/files.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/study/c++/first_server/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/socket_win.c$(ObjectSuffix): socket_win.c $(IntermediateDirectory)/socket_win.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/study/c++/first_server/socket_win.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/socket_win.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/socket_win.c$(DependSuffix): socket_win.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/socket_win.c$(ObjectSuffix) -MF$(IntermediateDirectory)/socket_win.c$(DependSuffix) -MM "socket_win.c"

$(IntermediateDirectory)/socket_win.c$(PreprocessSuffix): socket_win.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/socket_win.c$(PreprocessSuffix) "socket_win.c"

$(IntermediateDirectory)/struct_to_json.c$(ObjectSuffix): struct_to_json.c $(IntermediateDirectory)/struct_to_json.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/study/c++/first_server/struct_to_json.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/struct_to_json.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/struct_to_json.c$(DependSuffix): struct_to_json.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/struct_to_json.c$(ObjectSuffix) -MF$(IntermediateDirectory)/struct_to_json.c$(DependSuffix) -MM "struct_to_json.c"

$(IntermediateDirectory)/struct_to_json.c$(PreprocessSuffix): struct_to_json.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/struct_to_json.c$(PreprocessSuffix) "struct_to_json.c"

$(IntermediateDirectory)/list.c$(ObjectSuffix): list.c $(IntermediateDirectory)/list.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/study/c++/first_server/list.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/list.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/list.c$(DependSuffix): list.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/list.c$(ObjectSuffix) -MF$(IntermediateDirectory)/list.c$(DependSuffix) -MM "list.c"

$(IntermediateDirectory)/list.c$(PreprocessSuffix): list.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/list.c$(PreprocessSuffix) "list.c"

$(IntermediateDirectory)/xml.c$(ObjectSuffix): xml.c $(IntermediateDirectory)/xml.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/study/c++/first_server/xml.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/xml.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/xml.c$(DependSuffix): xml.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/xml.c$(ObjectSuffix) -MF$(IntermediateDirectory)/xml.c$(DependSuffix) -MM "xml.c"

$(IntermediateDirectory)/xml.c$(PreprocessSuffix): xml.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/xml.c$(PreprocessSuffix) "xml.c"

$(IntermediateDirectory)/db_manager.c$(ObjectSuffix): db_manager.c $(IntermediateDirectory)/db_manager.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/study/c++/first_server/db_manager.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/db_manager.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/db_manager.c$(DependSuffix): db_manager.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/db_manager.c$(ObjectSuffix) -MF$(IntermediateDirectory)/db_manager.c$(DependSuffix) -MM "db_manager.c"

$(IntermediateDirectory)/db_manager.c$(PreprocessSuffix): db_manager.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/db_manager.c$(PreprocessSuffix) "db_manager.c"

$(IntermediateDirectory)/files.c$(ObjectSuffix): files.c $(IntermediateDirectory)/files.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/study/c++/first_server/files.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/files.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/files.c$(DependSuffix): files.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/files.c$(ObjectSuffix) -MF$(IntermediateDirectory)/files.c$(DependSuffix) -MM "files.c"

$(IntermediateDirectory)/files.c$(PreprocessSuffix): files.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/files.c$(PreprocessSuffix) "files.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


