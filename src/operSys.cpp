#include "/home/mushroom/Проекты/C++/SystemCheck/Include/operSys.h"

#include <QMessageBox>
#include <QDir>
#include <QProcessEnvironment>

OS::OS() {
    paths = {{"/etc/os-release"}, {"/etc/hostname"}, {"/proc/sys/kernel/osrelease"}, {"/proc/uptime"}};
    fileReader = new FileReader(paths);
    parsedFiles = fileReader->getRefreshedVectorOfParsedFiles();

    loadOSInfo();
}

void OS::loadOSInfo(){
    comuterName = parsedFiles[1].first();
    kernelVersion = parsedFiles[2].first();
    userName = getUserNameFromSystem();
    desktopEnvironment = getDesktopEnvironmentFromSystem();

    for (const QMap<QString, QString>& currentMap : parsedFiles) {
        if (currentMap.contains("NAME")) {
            systemName = currentMap.value("NAME").remove('"') + " ";
        }
        if (currentMap.contains("VERSION")) {
            systemName += currentMap.value("VERSION").remove('"');
        }
        if (currentMap.contains("HOME_URL=\"https")) {
            homeURL = "https:" + currentMap.value("HOME_URL=\"https").remove('"');
        }
    }
}

QString OS::getDesktopEnvironmentFromSystem(){
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QString DesktopEnvironment = env.value("XDG_CURRENT_DESKTOP");
    if (DesktopEnvironment.isEmpty()) {
        DesktopEnvironment = env.value("DESKTOP_SESSION");
    }

    return DesktopEnvironment.isEmpty() ? "unknown" : DesktopEnvironment;
}

QString OS::getUserNameFromSystem() {
    QString user = QProcessEnvironment::systemEnvironment().value("USER");

    if (user.isEmpty()) {
        user = QDir::home().dirName();
    }

    return user;
}

QString OS::getSessionTime() {
    parsedFiles = fileReader->getRefreshedVectorOfParsedFiles();
    QString temp = parsedFiles[3].first().section(' ', 0, 0);
    double seconds = temp.toDouble();
    QString var;

    int totalSeconds = static_cast<int>(seconds);
    int days = totalSeconds / 86400;
    int hours = (totalSeconds % 86400) / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int secs = totalSeconds % 60;

    dayVariations(days, var);

    sessionTime = QString("%1%2%3:%4:%5")
        .arg(days)
        .arg(var)
        .arg(hours, 2, 10, QLatin1Char('0'))
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(secs, 2, 10, QLatin1Char('0'));

    return sessionTime;
}



void OS::dayVariations(int& days, QString& var){
    if(days == 1){
        var = " день ";
    }
    else if(days == 2 || days == 3 || days == 4){
        var = " дня ";
    }
    else var = " дней ";
}
