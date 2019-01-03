#include "turretResolver.h"

#include "pxr/pxr.h"
#include "pxr/usd/ar/defineResolver.h"
#include "pxr/usd/ar/assetInfo.h"
#include "pxr/usd/ar/resolverContext.h"

#include "pxr/base/arch/fileSystem.h"
#include "pxr/base/arch/systemInfo.h"
#include "pxr/base/tf/getenv.h"
#include "pxr/base/tf/fileUtils.h"
#include "pxr/base/tf/pathUtils.h"
#include "pxr/base/tf/staticData.h"
#include "pxr/base/tf/stringUtils.h"
#include "pxr/base/vt/value.h"

#include <tbb/concurrent_hash_map.h>
#include <iostream>
#include <string>

#include <turretClient.h>
#include <turretLogger.h>

PXR_NAMESPACE_OPEN_SCOPE

namespace {
    turret_client::turretClient g_zmq("usd");
}

AR_DEFINE_RESOLVER(TurretResolver, ArResolver);


TurretResolver::TurretResolver() : ArDefaultResolver()
{
    std::cout << "TURRET USD Resolver - Created Resolver\n\n";
}

TurretResolver::~TurretResolver()
{
    std::cout << "TURRET USD Resolver - Destroyed Resolver\n\n";
}

std::string
TurretResolver::Resolve(const std::string& path)
{
    return TurretResolver::ResolveWithAssetInfo(path, /* assetInfo = */ nullptr);
}

std::string
TurretResolver::ResolveWithAssetInfo(const std::string& path, ArAssetInfo* assetInfo) {
    // Check if path provided is of tank schema
    if(g_zmq.matches_schema(path)) {
        std::string query = path;

        // Check for USD_ASSET_TIME env var
        const std::string envUsdAssetTime = TfGetenv("USD_ASSET_TIME");

        // If time var exists, append asset time to query
        if(!envUsdAssetTime.empty()) {
            query += "&time=" + envUsdAssetTime;
        }

        turret_client::turretLogger::Instance()->Log("TURRET USD Resolver - using ala usd resolver for file path: " + query);

        return g_zmq.resolve_name(query);
    } else {

        turret_client::turretLogger::Instance()->Log("TURRET USD Resolver - using default resolver for file path: " + path);

        return ArDefaultResolver::ResolveWithAssetInfo(path, assetInfo);
    }
}

void
TurretResolver::UpdateAssetInfo(
    const std::string& identifier,
    const std::string& filePath,
    const std::string& fileVersion,
    ArAssetInfo* resolveInfo)
{
    ArDefaultResolver::UpdateAssetInfo(identifier, filePath, fileVersion, resolveInfo);
}

VtValue
TurretResolver::GetModificationTimestamp(
    const std::string& path,
    const std::string& resolvedPath)
{
    return ArDefaultResolver::GetModificationTimestamp(path, resolvedPath);
}

bool 
TurretResolver::FetchToLocalResolvedPath(
    const std::string& path,
    const std::string& resolvedPath)
{
    return true;

    /*if(g_zmq.matches_schema(path)) {
        return true;
    } else {
        return true;
    }*/
}

std::string
TurretResolver::GetExtension(const std::string& path)
{
    if(g_zmq.matches_schema(path)) {   
        // TODO: Query tank for extension
        return "usd";
    }
    return ArDefaultResolver::GetExtension(path);
}

PXR_NAMESPACE_CLOSE_SCOPE