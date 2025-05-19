#pragma once
#include "../../include/utils/ClientLogger.h"
#include "IPresenter.h"

namespace src
{
    class FlightPresenter : public IPresenter {
        ClientLogger log;
    public:
        FlightPresenter(std::ostream *output, std::istream *input): IPresenter(output, input) {}

        void getAllFlights();
        void createFlight();
    };
}