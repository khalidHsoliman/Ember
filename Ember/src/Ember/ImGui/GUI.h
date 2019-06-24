#pragma once

#include "imgui.h"
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

namespace Ember
{
	//Menu
	void ShowMainMenuBar();
	void ShowNewFileDialog(bool* dialog_new_active);
	void ShowOpenFileDialog(bool* dialog_open_active);
	void ShowLogWindow();
	void ShowInspector(bool* inspector_active);
	void ShowGUI(bool* p_open = NULL);
}