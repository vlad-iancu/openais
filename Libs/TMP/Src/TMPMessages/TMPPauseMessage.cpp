#include <TMPMessages/TMPPauseMessage.hpp>

#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

using namespace openais::TMP;

TMP_MESSAGE_IMPL(TMPPauseMessage)
