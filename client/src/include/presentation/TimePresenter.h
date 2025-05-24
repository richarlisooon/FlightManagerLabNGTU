#pragma once
#include "../../include/utils/ClientLogger.h"
#include "IPresenter.h"

namespace src
{
    class TimePresenter : public IPresenter {
        ClientLogger log;
    public:
        TimePresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

        void getCurrentTime();
        void addTime();
    };
}