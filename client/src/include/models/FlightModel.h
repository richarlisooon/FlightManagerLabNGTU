#pragma once

#include <string>

namespace src
{
    class FlightModel
    {
        long int _id;
        long int _timstampstart;
        long int _timestampend;
        long int _dispatcherId;
        long int _planeId;
        long int _airportId;
    public:
        FlightModel(long int id, long int timestampstart, long int timestampend, long int dispatcherId, long int planeId, long int airportId);

        long int getId();
        long int getTimestampStart();
        long int getTimestampEnd();
        long int getDispatcherId();
        long int getPlaneId();
        long int getAirportId();

        void setId(long int id);
        void setTimestampStart(long int timestampstart);
        void setTimestampEnd(long int timestampend);
        void setDispatcherId(long int dispatcherId);
        void setPlaneId(long int planeId);
        void setAirportId(long int airportId);

    };
}