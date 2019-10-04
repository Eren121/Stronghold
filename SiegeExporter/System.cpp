#include "System.h"

#ifdef _WIN32
#   include <Windows.h>
#   include <ShlObj.h>
#   include <QDir>
#   pragma comment(lib, "shell32.lib")

namespace System
{
    QString getMyDocumentsDirectoryPath()
    {
        WCHAR myDocuments[MAX_PATH];

        if(SHGetFolderPathW(nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, myDocuments) == S_OK) {
            return QString::fromWCharArray(myDocuments);
        }
        else {
            return QString();
        }
    }

    QString getSh2UserFolder()
    {
        return getMyDocumentsDirectoryPath() + "/Stronghold 2";
    }

    QString getS2hInstallFolder()
    {
        return "C:/Program Files (x86)/Steam/steamapps/common/Stronghold 2";
    }
}
#else

namespace System
{
    QString getMyDocumentsDirectoryPath()
    {
        return QDir::homePath() + "/Documents";
    }

    QString getSh2UserFolder()
    {
        return getMyDocumentsDirectoryPath() + "/Stronghold 2";
    }

    QString getS2hInstallFolder()
    {
        return QDir::homePath() + "/Stronghold/GameFiles";
    }
}

#endif
