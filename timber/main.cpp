#include "GameManager.h"

int main()
{
	GameManager gm;

	while (gm.GetWindow()->isOpen())
	{
		gm.PlayScene(new Title());
		if (gm.GetScene()->Loop())
			return 0;
		gm.ReleaseScene();
		
		SelectGameMode* sgm = new SelectGameMode();
		gm.PlayScene(sgm);
		if (gm.GetScene()->Loop())
			continue;
		gm.gameMode = sgm->GetGameMode();
		gm.ReleaseScene();

		SelectCharacter* sc = new SelectCharacter(gm.gameMode);
		gm.PlayScene(sc);
		if (gm.GetScene()->Loop())
			continue;
		gm.character1p = sc->GetCharacter1p();
		gm.character2p = sc->GetCharacter2p();
		gm.ReleaseScene();

		gm.PlayScene(new GamePlay(gm.gameMode, gm.character1p, gm.character2p));
		if (gm.GetScene()->Loop())
			continue;
		gm.ReleaseScene();
	}
	return 0;
}