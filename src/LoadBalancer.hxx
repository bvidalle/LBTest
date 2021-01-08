#pragma once

#include "Provider.hxx"

#include <string>
#include <map>

namespace test
{

class LoadBalancer
{
public:

    typedef enum InvocationMethod
    {
        RANDOM,
        ROUND_ROBIN
    } InvocationMethodType;

    LoadBalancer(int maxAllowedProviders,
                 int maxRequestsPerProvider,
                 InvocationMethodType method = RANDOM);

    LoadBalancer(LoadBalancer const&) = default;

    std::string Get();

    void RegisterNewProvider ( std::shared_ptr<test::Provider> provider );

    void SetInvocationMethod ( InvocationMethod method);

    // true: switches on ON, false: switches to OFF
    void SwitchInclusion ( std::string id , bool value );

    bool IsProviderIncluded ( std::string id );

    bool IsProviderValidForInvocation ( std::string id );

    void Check();

    int GetNbIncludedProviders();

    int GetNbRunningRequests();

private:

    int                                _maxAllowedProviders;

    int                                _maxRequestsPerProvider;

    typedef struct {
        std::shared_ptr<test::Provider> provider;
        bool                            state;
        int                             runCheckId;
        int                             nbRequests;
    } ProviderStructure;

    typedef std::map<int, ProviderStructure> MapProviderT;

    // container for the providers
    MapProviderT                       _mProvider;

    // specifies how the containers are invoked
    InvocationMethodType              _invocationMethod;

    // in case for round-robin selection we need to have a starting point
    bool                              _bRoundRobinInit;

    // preserves the iterator for quick selection of the next provider (round-robin)
    MapProviderT::iterator            _itRoundRobin;

    // Used to control two consecutive successful check() on a provider
    int                                  _runCheckId;

};

} //namespace test

