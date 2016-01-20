#ifndef __OIC_R_ICE_MAKER_H
#define __OIC_R_ICE_MAKER_H

#include "Resource.h"

using namespace OC;
namespace PH = std::placeholders;

/* Resource types */
const std::string OIC_R_ICE_MAKER = "oic.r.icemaker";

/* Attributes */
const std::string ICE_STATUS = "value";


class IceMaker : public Resource
{
public:
    IceMaker(std::string uri) : IceMaker(uri, false) {}

    IceMaker(std::string uri, bool secure) :
        Resource(uri,
                 OIC_R_ICE_MAKER,
                 OIC_IF_A,
                 secure)
    {
        m_rep.setValue<string>(ICE_STATUS, "full");
    }

protected:
    bool isValid(const OCRepresentation& rep)
    {
        if (!Resource::isValid(rep))
            return false;

        if (!checkType(rep, OIC_R_ICE_MAKER))
            return false;

        if (!checkInterface(rep, OIC_IF_A))
            return false;

        if (!checkAttr(rep, ICE_STATUS, AttributeType::String))
            return false;

        return true;
    }

    int put(const OCRepresentation& rep)
    {
        if (Resource::put(rep) < 0)
            return -1;

        std::string b =  rep.getValue<string>(ICE_STATUS);

        if (b != m_rep.getValue<string>(ICE_STATUS))
        {
            m_rep.setValue<string>(ICE_STATUS, b);

            return 1;
        }

        return 0;
    }
};
#endif