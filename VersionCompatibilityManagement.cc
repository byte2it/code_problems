#include <iostream>
#include <unordered_map>
#include <cassert>

using namespace std;

class VersionCompatibilityManagement {
    unordered_map<int, int> mm;

public:
    VersionCompatibilityManagement() {
        mm[0] = true;
    }

    void addNewVersion(int ver, bool isCompatibleWithPrev) {
        if (isCompatibleWithPrev)
            mm[ver] = mm[ver - 1];
        else
            mm[ver] = ver;
    }

    bool isCompatible(int srcVer, int targetVer) {
        return mm[srcVer] == mm[targetVer];
    }


};

int main()
{
    VersionCompatibilityManagement versions;
    versions.addNewVersion(1, false);
    versions.addNewVersion(2, true);
    versions.addNewVersion(3, true);
    versions.addNewVersion(4, false);
    versions.addNewVersion(5, true);
    versions.addNewVersion(6, true);

    assert(versions.isCompatible(1, 3) == true);
    assert(versions.isCompatible(3, 5) == false);
    assert(versions.isCompatible(4, 2) == false);
    assert(versions.isCompatible(3, 3) == true);
}
