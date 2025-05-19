#pragma once
#include "../../include/utils/ClientLogger.h"
#include "IPresenter.h"

namespace src
{
    class DispatcherPresenter : public IPresenter {
        ClientLogger log;
    public:
        DispatcherPresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

        void getDispatchers();
        void updateDispatcher();
        void getDispatcherById();
    };
}