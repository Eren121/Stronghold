#include "System.h"

#ifdef _WIN32
#   include <Windows.h>
#   include <ShlObj.h>
#else
#   include <QDir>
#endif

#ifdef _WIN32
#pragma(lib, "shell32.lib")
namespace System
{
    QString getMyDcoumentsDirectoryPath()
    {
        WCHAR myDocuments[MAX_PATH];

        if(SHGetFolderPathW(nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, myDocuments) == S_OK) {
            return QString::fromWCharArray(myDocuments);
        }
        else {
            return QString();
        }
        return QDir::homePath() + "/Documents";
    }

    QString getMyDocumentsDirectoryPath();
    QString getSh2UserFolder();
    QString getS2hInstallFolder();
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
