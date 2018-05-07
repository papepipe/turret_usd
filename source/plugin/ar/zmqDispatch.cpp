#include "zmqDispatch.h"

#include <iostream>
#include <ctime>

#include "../../external/zmq.hpp"

namespace usd_zmq
{
    // -- Public

    zmqDispatch::zmqDispatch() { }

    zmqDispatch::~zmqDispatch() { }

    std::string zmqDispatch::resolve_name(const std::string& a_path)
    {
        //std::cout << "ALA USD Resolver - resolving name: " << a_path << "\n\n";
        const auto parsed_path = this->parse_query(a_path);
        return parsed_path;
    }

    bool zmqDispatch::resolve_exists(const std::string& a_path)
    {
        const std::string parsed_path = zmqDispatch::resolve_name(a_path);
        if(parsed_path == "NOT_FOUND")
            return false;
        else 
            return true;
    }

    // Returns if path matches tank query schema
    bool zmqDispatch::matches_schema(const std::string& a_path)
    {
        return a_path.find(TANK_PREFIX_SHORT) == 0;
    }

    // -- Protected

    std::string zmqDispatch::parse_query(const std::string& a_query)
    {
        if(usd_zmq::ZMQ_CACHE_QUERIES) {
            // Search for cached result
            const auto cached_result = m_cachedQueries.find(a_query);

            if (cached_result != m_cachedQueries.end()) {
                //std::cout << "Current time: " << std::time(0) << "\n";
                //std::cout << "Cache time: " << cached_result->second.timestamp << "\n";
                // If cache is still fresh
                //if(std::time(0) - cached_result->second.timestamp <= usd_zmq::ZMQ_CACHE_TIMEOUT)
                std::cout << "ALA USD Resolver - Received Cached response: " << cached_result->second.resolved_path << "\n\n";
                //std::cout << "-------------------------------------------------------------------------------------------------------------\n\n\n\n";
                return cached_result->second.resolved_path;
            }
        }

        // Check socket status

        zmq::context_t m_context(1);
        zmq::socket_t m_socket(m_context, ZMQ_REQ);
    
        //std::cout << "ALA USD Resolver - Connecting to local zmq server..." << "\n";
        m_socket.connect("tcp://" + std::string(usd_zmq::ZMQ_SERVER) + ":" + std::string(usd_zmq::ZMQ_PORT));

        m_socket.setsockopt(ZMQ_LINGER, usd_zmq::ZMQ_TIMEOUT);
        m_socket.setsockopt(ZMQ_RCVTIMEO, usd_zmq::ZMQ_TIMEOUT);

        // Create zmq request
        zmq::message_t request(a_query.c_str(), a_query.length());
        
        // Send zmq request
        m_socket.send(request, ZMQ_NOBLOCK);

        // Wait for the reply
        zmq::message_t reply;
        m_socket.recv(&reply);
    
        // Store the reply
        std::string realPath = std::string((char *)reply.data());
        std::cout << "ALA USD Resolver - received real response: " << realPath << "\n\n";

        if(usd_zmq::ZMQ_CACHE_QUERIES) {
            // Cache reply
            zmqQueryCache cache = {realPath, std::time(0)};
            
            m_cachedQueries.insert(std::make_pair(a_query, cache));
        }

        m_socket.close();
        m_context.close();

        return realPath;
    }
}