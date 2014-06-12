#pragma once
#include "BWAPI.h"
#include "Gateway.h"
#include "Defines.h"

namespace Lizurd
{

	class LizurdModule : public BWAPI::AIModule
	{
	public:
		LizurdModule(void){};
		~LizurdModule(void);

		virtual void onStart();
		virtual void onEnd(bool isWinner) override;
		virtual void onFrame() override;
		virtual void onSendText(std::string text) override;
		virtual void onReceiveText(BWAPI::Player player, std::string text) override;
		virtual void onPlayerLeft(BWAPI::Player player) override;
		virtual void onNukeDetect(BWAPI::Position target) override;
		virtual void onUnitDiscover(BWAPI::Unit unit) override;
		virtual void onUnitEvade(BWAPI::Unit unit) override;
		virtual void onUnitShow(BWAPI::Unit unit) override;
		virtual void onUnitHide(BWAPI::Unit unit) override;
		virtual void onUnitCreate(BWAPI::Unit unit) override;
		virtual void onUnitDestroy(BWAPI::Unit unit) override;
		virtual void onUnitMorph(BWAPI::Unit unit) override;
		virtual void onUnitRenegade(BWAPI::Unit unit) override;
		virtual void onSaveGame(std::string gameName) override;
		virtual void onUnitComplete(BWAPI::Unit unit) override;

		/// <summary>
		/// Remove the items in toRemove from vec
		/// </summary>
		/// <param name="vec">The vector to remove from.</param>
		/// <param name="toRemove">The vector of items to remove.</param>
		template<class T>
		static void VectorRemove(std::vector<T> &vec, const std::vector<T> &toRemove)
		{
			for(std::vector<T>::const_iterator it = toRemove.begin(); it != toRemove.end(); ++it)
			{
				std::vector<T>::iterator found = std::find(vec.begin(), vec.end(), *it);
				if(found != vec.end())
					vec.erase(found);
			}
		}

	private:
		Result _initialised;
	};

}