#include "PathUtils.h"

std::string getExecutablePath() {
    static std::string cachedPath;
    if (!cachedPath.empty()) {
        return cachedPath;
    }
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    cachedPath = (count != -1) ? std::string(result, count) : std::string();
    return cachedPath;
}

std::string getProjectDirectory() {
    std::string executablePath = getExecutablePath();
    size_t lastSlash = executablePath.find_last_of('/');
    if (lastSlash != std::string::npos) {
        return executablePath.substr(0, lastSlash);
    }
    return std::string();
}

std::string getResourcePath(const std::string& resourcePath) {
    std::string projectDir = getProjectDirectory();
    if (projectDir.empty()) {
        return resourcePath;
    }
    return projectDir + "/" + resourcePath;
}
