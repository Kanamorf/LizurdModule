#include "LizurdModule.h"
#include "RaceDescriptor.h"
#include "Notification.h"
#include "Logger.h"

#define FRAMESPERAI 15

using namespace BWAPI;
using namespace Filter;
using Lizurd::LizurdModule;

void LizurdModule::onStart()
{
	//Initialise everything once we know what race we are playing
	BWAPI::Race race = Broodwar->self()->getRace();
	_initialised = _gateway.Initialise(BroodwarPtr, race);
	if(_initialised != Result::Success)
	{
		Broodwar->sendText("Failed to initialise the bot, most likely as it only works with Zerg.");
	}
	Logger::GetInstance().Log("LizurdModule", "We are playing: " + race.getName());
	Broodwar->setLocalSpeed(10);
}

void LizurdModule::onEnd(bool isWinner)
{
	if (!Broodwar->isReplay())
	{
		std::stringstream ss;
		ss << "*** Game over: Average FPS : " << Broodwar->getAverageFPS();
		Logger::GetInstance().Log("LizurdModule", ss.str());


	}
	// Called when the game ends
	if ( isWinner )
	{
		// Log your win here!
	}
}

void LizurdModule::onFrame()
{
	if(_initialised == Result::Success)
	{
		// Called once every game frame
		if(Broodwar->getFrameCount()%FRAMESPERAI == 0)
		{
			Logger::GetInstance().Log("LizurdModule", "Starting Update");
			_gateway.Update(Broodwar->getFrameCount());
		}
		if(Broodwar->getFrameCount() > FRAMESPERAI)
		{
			Broodwar->drawBox(BWAPI::CoordinateType::Screen, 320, 0, 420, 20, BWAPI::Colors::Blue);
			Notification notification(ResourceCoord);
			notification.SetAction(Action::CurrentResources);
			if(_gateway.RegisterNotification(notification) == Result::Success)
			{
				std::stringstream ss;
				//																														  (the internal supply is twice the displayed supply)
				//																													      (this is because zerglings are half a supply)
				ss << "M: " << notification.GetResourceValue().Minerals << " V: " << notification.GetResourceValue().Vespene << " S: " << (notification.GetResourceValue().Supply /2 );
				Broodwar->drawText(BWAPI::CoordinateType::Screen, 330, 5, ss.str().c_str());

	#ifdef _DEBUG
				_gateway.DrawDebugInfo();
	#endif
			}
		}
	}
}

void LizurdModule::onSendText(std::string text)
{

	// Send the text to the game if it is not being processed.
	Broodwar->sendText("%s", text.c_str());


	// Make sure to use %s and pass the text as a parameter,
	// otherwise you may run into problems when you use the %(percent) character!

}

void LizurdModule::onReceiveText(BWAPI::Player player, std::string text)
{
	// Parse the received text
	Broodwar << player->getName() << " said \"" << text << "\"" << std::endl;
}

void LizurdModule::onPlayerLeft(BWAPI::Player player)
{
	// Interact verbally with the other players in the game by
	// announcing that the other player has left.
	Broodwar->sendText("Goodbye %s!", player->getName().c_str());
}

void LizurdModule::onNukeDetect(BWAPI::Position target)
{

	// Check if the target is a valid position
	if ( target )
	{
		// if so, print the location of the nuclear strike target
		Broodwar << "Nuclear Launch Detected at " << target << std::endl;
	}
	else 
	{
		// Otherwise, ask other players where the nuke is!
		Broodwar->sendText("Where's the nuke?");
	}

	// You can also retrieve all the nuclear missile targets using Broodwar->getNukeDots()!
}

void LizurdModule::onUnitDiscover(BWAPI::Unit unit)
{
}

void LizurdModule::onUnitEvade(BWAPI::Unit unit)
{
}

void LizurdModule::onUnitShow(BWAPI::Unit unit)
{
}

void LizurdModule::onUnitHide(BWAPI::Unit unit)
{
}

void LizurdModule::onUnitCreate(BWAPI::Unit unit)
{
	if(_initialised == Result::Success)
	{
		if (!Broodwar->isReplay())
		{
			if(unit->getPlayer() == Broodwar->self())
			{
				Notification notification(UnitDiscoveryCoord);
				notification.SetAction(Action::RegisterUnit);
				notification.AddUnit(unit);
				_gateway.RegisterNotification(notification);
			}
		}
	}
}

void LizurdModule::onUnitDestroy(BWAPI::Unit unit)
{
	if(_initialised == Result::Success)
	{
		if (!Broodwar->isReplay())
		{
			if(unit->getPlayer() == Broodwar->self())
			{
				Notification notification(UnitDiscoveryCoord);
				notification.SetAction(Action::DeRegisterUnit);
				notification.AddUnit(unit);
				_gateway.RegisterNotification(notification);
			}
		}
	}
}

void LizurdModule::onUnitMorph(BWAPI::Unit unit)
{
	if(_initialised == Result::Success)
	{
		if (!Broodwar->isReplay())
		{
			if(unit->getPlayer() == Broodwar->self())
			{
				Notification notification(UnitDiscoveryCoord);
				notification.SetAction(Action::MorphUnit);
				notification.AddUnit(unit);
				notification.SetFrame(Broodwar->getFrameCount());
				_gateway.RegisterNotification(notification);
			}
		}
	}
}

void LizurdModule::onUnitRenegade(BWAPI::Unit unit)
{
}

void LizurdModule::onSaveGame(std::string gameName)
{
	Broodwar << "The game was saved to \"" << gameName << "\"" << std::endl;
}

void LizurdModule::onUnitComplete(BWAPI::Unit unit)
{
}
