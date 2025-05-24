#pragma once
#include "../../include/utils/ClientLogger.h"
#include "IPresenter.h"

namespace src
{
    class IdentityPresenter : public IPresenter {
        ClientLogger log;
    public:
        IdentityPresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

        bool login();
        bool registerDispatcher();
    };
}