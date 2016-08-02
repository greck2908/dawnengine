/*
 * Dawn Engine
 * Written by David Avedissian (c) 2012-2016 (git@davedissian.com)
 */
#include "Common.h"
#include "core/Context.h"

namespace dw {

Context::Context(String basePath, String prefPath) : mBasePath(basePath), mPrefPath(prefPath) {
}

Context::~Context() {
}

void Context::addSubsystem(Object* subsystem) {
    mSubsystems[subsystem->getType()] = SharedPtr<Object>(subsystem);
}

}
