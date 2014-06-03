#include "LizurdModule.h"

using namespace BWAPI;
using namespace Filter;

void LizurdModule::onStart()
{
  // Hello World!
  Broodwar->sendText("Hello world!");
}

void LizurdModule::onEnd(bool isWinner)
{
  // Called when the game ends
  if ( isWinner )
  {
    // Log your win here!
  }
}

void LizurdModule::onFrame()
{
  // Called once every game frame

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
}

void LizurdModule::onUnitDestroy(BWAPI::Unit unit)
{
}

void LizurdModule::onUnitMorph(BWAPI::Unit unit)
{
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