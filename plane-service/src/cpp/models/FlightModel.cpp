#include "../../header/models/FlightModel.h"

FlightModel::FlightModel(long int id, long int timestampstart, long int timestampend, long int dispatcherId, long int planeId, long int airportId)
{
    _id = id;
    _timstampstart = timestampstart;
    _timestampend = timestampend;
    _dispatcherId = dispatcherId;
    _planeId = planeId;
    _airportId = airportId;
}


long int FlightModel::getId()
{
    return _id;
}
long int FlightModel::getTimestampStart()
{
    return _timstampstart;
}
long int FlightModel::getTimestampEnd()
{
    return _timestampend;
}
long int FlightModel::getDispatcherId()
{
    return _dispatcherId;
}
long int FlightModel::getPlaneId()
{
    return _planeId;
}
long int FlightModel::getAirportId()
{
    return _airportId;
}

void FlightModel::setId(long int id)
{
    _id = id;
}
void FlightModel::setTimestampStart(long int timestampstart)
{
    _timstampstart = timestampstart;
}
void FlightModel::setTimestampEnd(long int timestampend)
{
    _timestampend = timestampend;
}
void FlightModel::setDispatcherId(long int dispatcherId)
{
    _dispatcherId = dispatcherId;
}
void FlightModel::setPlaneId(long int planeId)
{
    _planeId = planeId;
}
void FlightModel::setAirportId(long int airportId)
{
    _airportId = airportId;
}



