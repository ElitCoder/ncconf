#include "Configuration.h"
#include "Log.h"

int main() {
    if (!Configuration::parse()) {
        Log(ERR) << "FAILED TO PARSE WITH ERROR " << Configuration::error();
    }

    return 0;
}