#pragma once

#include "io.h"
#include "input.h"
#include "output.h"

using namespace testutil;

bool checker(istream& inStream, istream& outStream, istream& ansStream) {
//    Input in(inStream);
//    Input out(outStream);
//    Input ans(ansStream);

    return compareStreams(inStream, outStream, ansStream);
}
