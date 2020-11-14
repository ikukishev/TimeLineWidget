#include "ITimeLineTrackViev.h"

std::shared_ptr<std::list< ITrackFactory* >> ITrackFactory::sTrackFactories;

ITrackFactory::ITrackFactory()
{
   initTrackFactories().push_back( this );
}

const std::list<ITrackFactory *> &ITrackFactory::trackFactories()
{
   return initTrackFactories();
}

std::list<ITrackFactory *> &ITrackFactory::initTrackFactories()
{
   if ( nullptr == sTrackFactories )
   {
      sTrackFactories = std::make_shared<std::list<ITrackFactory *>>();
   }
   return *sTrackFactories;
}
