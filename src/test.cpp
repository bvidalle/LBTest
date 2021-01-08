//============================================================================
// Name        : test.cpp
// Author      : Bernard Vidalleinc
//============================================================================

#include "Provider.hxx"
#include "LoadBalancer.hxx"

#include <iostream>
#include <vector>

static const size_t maxAllowedProviders = 10;
static const size_t maxRequestsPerProvider = 10;

int main()
{

    // Step 1
    std::vector<std::shared_ptr<test::Provider> > vProvider;

    std::cout << "Starting the load balancer with a maximum capacity of "
            << maxAllowedProviders << " providers and " << maxRequestsPerProvider << " requests per provider" << std::endl;
    test::LoadBalancer lb ( maxAllowedProviders , maxRequestsPerProvider );

    // Step 2
    std::cout << "Step 2 : Registering a list of " << maxAllowedProviders << " providers to the load balancer..." << std::endl;
    for ( int i = 1; i <= maxAllowedProviders; i++ )
    {
        vProvider.push_back(std::make_shared<test::Provider>());
        lb.RegisterNewProvider(vProvider.back());
        std::cout << "         --> successfully added provider id " << vProvider.back()->Get() << std::endl;
    }

    std::cout << "Step 2 : Provider " << vProvider.back()->Get() << " already registered" << std::endl;
    try
    {
        lb.RegisterNewProvider(vProvider.back());
    }
    catch ( const std::string & e )
    {
        std::cout << "         --> " << e << std::endl;
    }

    std::cout << "Step 2 : Maximum number of providers reached" << std::endl;
    try
    {
        lb.RegisterNewProvider(std::make_shared<test::Provider>());
    }
    catch ( const std::string & e )
    {
        std::cout << "         --> " << e << std::endl;
    }

    // Step 3
    int iNbInvocation = maxAllowedProviders * 2;

    std::cout << "Step 3 : Random invocation (" << iNbInvocation << ") times" << std::endl;

    for ( int i = 1; i <= iNbInvocation; i++ )
    {
        std::cout << i;
        std::cout << "         --> Retrieved provider id " << lb.Get() << std::endl;
    }

    // Step 4
    std::cout << "Step 4 : Round-Robin invocation (" << iNbInvocation << ") times" << std::endl;
    // switches the load balancer invocation method from default (RANDOM) to ROUND_ROBIN
    lb.SetInvocationMethod ( test::LoadBalancer::InvocationMethod::ROUND_ROBIN );
    for ( int i = 1; i <= iNbInvocation; i++ )
    {
        std::cout << i;
        std::cout << "         --> Retrieved provider id " << lb.Get() << std::endl;
    }

    // Step 5
    std::cout << "Step 5 : Node exclusion-inclusion" << std::endl;
    std::cout << "Step 5 : Displaying default state (expected value = 1(ON))" << std::endl;
    for ( int i = 1; i <= maxAllowedProviders; i++ )
    {
        auto id = lb.Get();
        std::cout << "         --> Retrieved provider id " << id << " with state " <<
                   lb.IsProviderIncluded(id) << std::endl;
    }
    std::cout << "Step 5 : Displaying current state (expected value = 0(OFF))" << std::endl;
    for ( int i = 1; i <= maxAllowedProviders; i++ )
    {
        auto id = lb.Get();
        lb.SwitchInclusion(id,false);
        std::cout << "         --> Retrieved provider id " << id << " with state " <<
                   lb.IsProviderIncluded(id) << std::endl;
    }

    std::cout << "Step 5 : All providers are disconnected" << std::endl;
    try
    {
        lb.Get();
    }
    catch ( const std::string & e )
    {
        std::cout << "         --> " << e << std::endl;
    }

    std::cout << "Step 5 : Activating only the last provider in the list (" << vProvider.back()->Get() << ")" <<  std::endl;;
    lb.SwitchInclusion(vProvider.back()->Get(),true);

    lb.SetInvocationMethod ( test::LoadBalancer::InvocationMethod::RANDOM );
    std::cout << "         --> RANDOM retrieved provider id " << lb.Get() << std::endl;
    lb.SetInvocationMethod ( test::LoadBalancer::InvocationMethod::ROUND_ROBIN );
    std::cout << "         --> ROUND_ROBIN retrieved provider id " << lb.Get() << std::endl;

    // Step 7
    std::cout << "Step 7 : heartbeat check" << std::endl;
    lb.Check();
    std::cout << "Step 7 : disconnecting all providers" << std::endl;
    for ( auto provider : vProvider )
    {
        provider->SetState(false);
    }
    std::cout << "Step 7 : check()" << std::endl;
    lb.Check();
    std::cout << "Step 7 : counting included providers, expected result is 0" << std::endl;
    std::cout << "         --> Found " << lb.GetNbIncludedProviders() << " included provider(s)" << std::endl;
    std::cout << "Step 7 : reconnecting all providers" << std::endl;
    for ( auto provider : vProvider )
    {
        provider->SetState(true);
    }
    std::cout << "Step 7 : check()" << std::endl;
    lb.Check();
    std::cout << "Step 7 : counting included providers, expected result is 0" << std::endl;
    std::cout << "         --> Found " << lb.GetNbIncludedProviders() << " included provider(s)" << std::endl;
    std::cout << "Step 7 : check()" << std::endl;
    lb.Check();
    std::cout << "Step 7 : counting included providers, expected result is " << vProvider.size() << std::endl;
    std::cout << "         --> Found " << lb.GetNbIncludedProviders() << " included provider(s)" << std::endl;

    std::cout << "Step 8 : Cluster capacity limit reached" << std::endl;
    std::cout << "Step 8 : Create a load balancer with " << maxAllowedProviders << " providers" << std::endl;
    test::LoadBalancer lb2 ( maxAllowedProviders , maxRequestsPerProvider );
    vProvider.clear();
    for ( int i = 1; i <= maxAllowedProviders; i++ )
    {
        vProvider.push_back(std::make_shared<test::Provider>());
        lb2.RegisterNewProvider(vProvider.back());
        std::cout << "         --> successfully added provider id " << vProvider.back()->Get() << std::endl;
    }
    lb2.SetInvocationMethod ( test::LoadBalancer::InvocationMethod::ROUND_ROBIN );

    std::cout << "Step 8 : Call Get() until exhaustion" << std::endl;
    try
    {
        while ( true )
        {
            std::cout << lb2.Get() << std::endl;
        }
    }
    catch ( const std::string & e )
    {
        std::cout << "         --> " << e << std::endl;
    }

    std::cout << "Successful completion" << std::endl;
    return 0;
}
