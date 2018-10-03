

#ifdef USE_WEBSERVER
	#ifdef Use_Relay
		const char HTTP_FORM_RELAY[] PROGMEM =
			"<form method='get' action='sv'>"
			"<input id='w' name='w' value='7' hidden><input id='r' name='r' value='0' hidden>";
		const char HTTP_FORM_RELAY2[] PROGMEM =
			"<fieldset><legend><b>&nbsp; " D_RELAY_NAME " {1</b>&nbsp;</legend>"
			"<table><tr><td><input id = 'b{1' name = 'b{1' type = 'radio' value = '0'{5></td><td><b>Manu</b></td><td>" D_PULSETIMER_OFF "</td></tr>"
			"<tr><td><input id = 'b{1' name = 'b{1' type = 'radio' value = '2'{6></td><td><b>" D_TIMER_ON "</b></td>"
			"<td><input id = 'i{1' name = 'i{1' placeholder = '0/00:00' value = '{7'></td></tr>"
			"<tr><td>----</td><td>"
			"<select id='m{1' name 'm{1' onchange='oc({1,this.value);'><option value='0'>" D_ALLDAY "</option>{o1{o2{o3{o4{o5{o6{o7</select>"
			"</td><td><input id = 'j{1' name = 'j{1' placeholder = '0/00:00' value = '{8'></td></tr>"
			"<tr><td><input id = 'b{1' name = 'b{1' type = 'radio' value = '1'{4></td><td><b>" D_PULSETIMER_ON "</b></td>"
			"<td><input id = 'a{1' name = 'a{1' placeholder = '00:00:30' value = '{3'></td></tr></table>"
			#ifdef USE_SENDOFF
				"" D_SEND_OFF "<input id = 'k{1' name = 'k{1' value = '{9'>"
			#endif
			"</fieldset>";
			// function on change ld
			const char HTTP_FORM_REALYSCRIPT[] PROGMEM = "function oc(i,j){"
			"document.getElementById('i' + i).value =j+'/0:0';"
			"document.getElementById('j' + i).value =j+'/0:0';"
			"}</script>";

		const char HTTP_FORM_RELAY3[] PROGMEM =
			"<fieldset><legend><b>&nbsp; " D_INTERLOCK_TITLE "</b> &nbsp;</legend>"
			"<input style = 'width:10%;' id = 'b14' name = 'b14' type = 'radio' value = '0'{5> <b>" D_INTERLOCK_NO "</b><br/> "
			"<input style = 'width:10%;' id = 'b14' name = 'b14' type = 'radio' value = '1'{4> <b>" D_INTERLOCK_YES "</b> "
			#ifdef USE_InterlockDelay
			"<br/> " D_INTERLOCK_TIME " <input id='t1' name='t1'  value='{t1'>"
			#endif
			#ifdef USE_SENDOFF
			"<br/> " D_SENDOFFURL " <input id='u1' name='u1' value='{u1'>"
			#endif
			"</fieldset>";
		void HandleRelayConfiguration()
		{
			if (HttpUser()) {
				return;
			}
			AddLog_P(LOG_LEVEL_DEBUG, S_LOG_HTTP, S_CONFIGURE_RELAY);
			char stemp[40];
			String page = FPSTR(HTTP_HEAD);
			page.replace(F("{v}"), FPSTR(S_CONFIGURE_RELAY));
			page.replace(F("</script>"), FPSTR(HTTP_FORM_REALYSCRIPT));
			page += FPSTR(HTTP_FORM_RELAY);
			//page += F("<br/>");

			uint8_t maxfn = (devices_present > MAX_FRIENDLYNAMES) ? MAX_FRIENDLYNAMES : devices_present;
			for (byte i = 0; i < maxfn; i++) {
				page += FPSTR(HTTP_FORM_RELAY2);
				page.replace(F("{1"), String(i + 1));
				//snprintf_P(stemp, sizeof(stemp), PSTR(D_RELAY_NAME"%d"), i + 1);
				page.replace(F("{2"), D_CONFIGURATION);
				page.replace(F("{9"), Settings.Outtimer[i]);

				if (Settings.pulseon_timer[i] > 0) {
					page.replace(F("{6"), F(" checked"));
					page.replace(F("{4"), "");
					page.replace(F("{5"), "");
					snprintf_P(stemp, sizeof(stemp), PSTR("%d/%d:%d"), (Settings.pulse_timer[i]>1440) ? ((Settings.pulse_timer[i] / 1440) % 9) : 0,
						(Settings.pulse_timer[i] > 60) ? ((Settings.pulse_timer[i]) % 1440) / 60 : 0, Settings.pulse_timer[i] % 60);
					page.replace(F("{8"), stemp);
					snprintf_P(stemp, sizeof(stemp), PSTR("%d/%d:%d"), (Settings.pulseon_timer[i]>1440) ? ((Settings.pulseon_timer[i] / 1440) % 9) : 0,
						(Settings.pulseon_timer[i] > 60) ? ((Settings.pulseon_timer[i]) % 1440) / 60 : 0, Settings.pulseon_timer[i] % 60);
					page.replace(F("{7"), stemp);
					page.replace(F("{3"), "");
					page.replace(F("{p1"), "0");
				}
				else {
					page.replace(F("{4"), (Settings.pulse_timer[i] > 0) ? F(" checked") : F(""));
					page.replace(F("{5"), (Settings.pulse_timer[i] == 0) ? F(" checked") : F(""));
					page.replace(F("{6"), "");
					page.replace(F("{7"), "");
					page.replace(F("{8"), "");
					snprintf_P(stemp, sizeof(stemp), PSTR("%d:%d:%d"), (Settings.pulse_timer[i]>3700) ? (Settings.pulse_timer[i] - 100) / 3600 : 0,
						(Settings.pulse_timer[i] > 160) ? ((Settings.pulse_timer[i] - 100) % 3600) / 60 : 0, (Settings.pulse_timer[i] > 110) ? (Settings.pulse_timer[i] - 100) % 60 : Settings.pulse_timer[i] / 10);
					page.replace(F("{3"), stemp);
					snprintf_P(stemp, sizeof(stemp), "%d", int(Settings.pulseon_timer[i] / 1440));
					page.replace(F("{p1"), stemp);
				}
				char arg[4];
				char sjour[4] = "123";
				for (byte j = 1; j< 8; j++) {
					String Ujour = D_DAY3LIST;
					sjour[0] = Ujour[j * 3 - 3];
					sjour[1] = Ujour[j * 3 - 2];
					sjour[2] = Ujour[j * 3 - 1];
					snprintf_P(stemp, sizeof(stemp), "<option value='%d'{y%d>%s</option>", j, j, sjour);
					snprintf_P(arg, 4, PSTR("{o%d"), j);
					page.replace(arg, stemp);
					page.replace("{y" + String(j), (((Settings.pulseon_timer[i] / 1440) % 9) == j) ? F(" selected ") : F(" "));
				}
			}
			//page += F("<br/>");
			if (devices_present > 1){
				page += FPSTR(HTTP_FORM_RELAY3);
				page.replace(F("{4"), (Settings.flag.interlock > 0) ? F(" checked") : F(""));
				page.replace(F("{5"), (Settings.flag.interlock == 0) ? F(" checked") : F(""));
				#ifdef USE_InterlockDelay
					snprintf_P(stemp, sizeof(stemp), kDecim, Settings.delay_InterlockOff);
					page.replace(F("{t1"), stemp);
				#endif
				#ifdef USE_SENDOFF
					snprintf_P(stemp, sizeof(stemp), kString, Settings.ota_url);
					page.replace(F("{u1"), stemp);
				#endif
			}


			page += FPSTR(HTTP_FORM_END);
			page += FPSTR(HTTP_BTN_CONF);
			ShowPage(page);
		} // end handle realy
		int TimerRelay(char * svalue, int sizeofvalue, boolean with110sec) {
			// try to find hrs , min and seconde from string given by user
			int shrs = 0;
			int smin = 0;
			int ssec = 0;
			int pos = 1;
			//snprintf_P(log_data, sizeof(log_data), "ini : %d %d %d %s", shrs, pos, sizeofvalue, svalue);
			//AddLog(LOG_LEVEL_INFO);

			if (!strlen(svalue)) {
				shrs = 0;
				smin = 0;
				ssec = 0;
				//snprintf_P(log_data, sizeof(log_data), "value = 0");
				//AddLog(LOG_LEVEL_INFO);
				return 0;
			}
			else {
				if (!with110sec) {
					// time with day d/h:m
					ssec = atoi(svalue); // set day in ssec
					for (byte d = 0; d <sizeofvalue; d++)
					{
						if (svalue[d] == '/') {
							for (byte db = 0; db < sizeofvalue - pos; db++)
							{
								svalue[db] = svalue[db + pos];
							}
							break;
						}
						else { pos = pos + 1; }
					}
					for (byte d = 1; d <= pos; d++)
					{
						svalue[sizeofvalue - d] = ' ';
					}
					//snprintf_P(log_data, sizeof(log_data), "Jrs : %d %d %d %s", ssec, pos, sizeofvalue, svalue);
					//AddLog(LOG_LEVEL_INFO);

				}
				shrs = atoi(svalue);
				pos = 1;
				for (byte d = 0; d <sizeofvalue; d++)
				{
					if (svalue[d] == ':') {
						for (byte db = 0; db < sizeofvalue - pos; db++)
						{
							svalue[db] = svalue[db + pos];
						}
						break;
					}
					else { pos = pos + 1; }
				}
				for (byte d = 1; d <= pos; d++)
				{
					svalue[sizeofvalue - d] = ' ';
				}

				//snprintf_P(log_data, sizeof(log_data), "Hrs : %d %d %d %s", shrs, pos, sizeofvalue, svalue);
				//AddLog(LOG_LEVEL_INFO);
				smin = atoi(svalue);
				if (with110sec) {
					// time with seconde (h:m:s)
					pos = 1;
					for (byte d = 0; d <sizeofvalue; d++)
					{
						if (svalue[d] == ':') {
							for (byte db = 0; db < sizeofvalue - pos; db++)
							{
								svalue[db] = svalue[db + pos];
							}
							break;
						}
						else { pos = pos + 1; }
					}
					for (byte d = 1; d <= pos; d++)
					{
						svalue[sizeofvalue - d] = ' ';
					}
					//snprintf_P(log_data, sizeof(log_data), "Min : %d %d %d %s", smin, pos, sizeofvalue, svalue);
					//AddLog(LOG_LEVEL_INFO);
					ssec = atoi(svalue);
				}
				if (!with110sec) {
					// to pulseon (day, hour, min
					return  ssec * 1440 + shrs * 60 + smin;
				}
				else {
					// to pulse(off) hour, min, sec if more than 110 else 0.01 seconde 
					if (shrs * 3600 + smin * 60 + ssec > 10) {
						return shrs * 3600 + smin * 60 + ssec + 100;
					}
					else {
						return ssec + 110;
					}
				}


			}
		}// end timer relay
	#endif
	void CP_HandleSaveSetting() {
		#ifdef Use_Relay // add cpat

			// save pulse_timer depend on radio button and input value for relay between 1 to 4
			/* snprintf_P(log_data, sizeof(log_data), "Save new value 1");
			AddLog(LOG_LEVEL_INFO);*/
			char svalue[9] = "";
			int stimer = 0;
			char Arg[3] = "a1";
			for (byte i = 0; i < ((devices_present <4) ? devices_present : 4); i++) {
				// for each relais save parameters

				snprintf_P(Arg, 3, PSTR("b%d"), i + 1);
				/* debug
				snprintf_P(log_data, sizeof(log_data), "Save arg 2 %d %s", i, Arg);
				AddLog(LOG_LEVEL_INFO); */
				stimer = (!strlen(WebServer->arg(Arg).c_str())) ? 0 : atoi(WebServer->arg(Arg).c_str());
				if (stimer == 1) {
					// timer
					/* degug
					snprintf_P(log_data, sizeof(log_data), "Sauve tim %d", i);
					AddLog(LOG_LEVEL_INFO);
					*/
					snprintf_P(Arg, 3, PSTR("a%d"), i + 1);
					/* debug
					snprintf_P(log_data, sizeof(log_data),"Sauve arg %d %s",i,Arg );
					AddLog(LOG_LEVEL_INFO); */
					snprintf_P(svalue, sizeof(svalue), kString, WebServer->arg(Arg).c_str());
					stimer = TimerRelay(svalue, sizeof(svalue), true);
				}
				else {
					if (stimer != 0) {
						// clock (value 2)

						//timer on
						snprintf_P(Arg, 3, PSTR("i%d"), i + 1);
						/* debug
						snprintf_P(log_data, sizeof(log_data), "Save arg 2 %d %s", i, Arg);
						AddLog(LOG_LEVEL_INFO); */
						snprintf_P(svalue, sizeof(svalue), kString, WebServer->arg(Arg).c_str());
						stimer = TimerRelay(svalue, sizeof(svalue), false);
						/* debug */
						snprintf_P(log_data, sizeof(log_data), "Save time 2 %d %d", i, stimer);
						AddLog(LOG_LEVEL_INFO);
						Settings.pulseon_timer[i] = stimer;
						//snprintf_P(Arg, 3, PSTR("a%d"), i + 1);
						snprintf_P(Arg, 3, PSTR("j%d"), i + 1);
						/* debug*/
						snprintf_P(log_data, sizeof(log_data), "Sauve arg %d %s", i, Arg);
						AddLog(LOG_LEVEL_INFO);
						snprintf_P(svalue, sizeof(svalue), kString, WebServer->arg(Arg).c_str());
						stimer = TimerRelay(svalue, sizeof(svalue), false);
					}
				}
				/* debug*/
				snprintf_P(log_data, sizeof(log_data), "Save time %d %d", i, stimer);
				AddLog(LOG_LEVEL_INFO);
				Settings.pulse_timer[i] = stimer;

				#ifdef USE_SENDOFF
					snprintf_P(Arg, 3, PSTR("k%d"), i + 1);
					/* debug
					snprintf_P(log_data, sizeof(log_data), "Save arg 2 %d %s", i, Arg);
					AddLog(LOG_LEVEL_INFO); */
					strlcpy(Settings.Outtimer[i], (!strlen(WebServer->arg(Arg).c_str())) ? "" : WebServer->arg(Arg).c_str(), 30);
				#endif
			}
			snprintf_P(svalue, sizeof(svalue), WebServer->arg("b14").c_str());
			Settings.flag.interlock = atoi(svalue);
			#ifdef USE_InterlockDelay
				if (atoi(svalue) > 0) {
					// set delay _interleock off cause interlock on
					snprintf_P(svalue, sizeof(svalue), WebServer->arg("t1").c_str());
					Settings.delay_InterlockOff = atoi(svalue);
				}
			#endif
			#ifdef USE_SENDOFF
				// set ota url use to send off message
				strlcpy(Settings.ota_url, (!strlen(WebServer->arg(F("u1")).c_str())) ? "" : WebServer->arg(F("u1")).c_str(), 100);
			#endif
			snprintf_P(log_data, sizeof(log_data), PSTR(D_RELAY_NAME " %d, %d, %d, %d %d %d"),
				Settings.pulse_timer[0], Settings.pulse_timer[1], Settings.pulse_timer[2], Settings.pulse_timer[3], Settings.flag.interlock, Settings.pulseon_timer[1]);
			AddLog(LOG_LEVEL_INFO);


		#endif
		} // end cp_HandleSaveSetting
#endif

void CP_PerformEverySecond()
{
	// restart every hour cause secure wifi AP rule
	#ifdef Reset_Every6Hours
		init_counter--;
		if ((init_counter <= 0) && (pulse_timer[0] = 0) && (pulse_timer[1] = 0) && (pulse_timer[2] = 0) && (pulse_timer[3] = 0)) {
			init_counter = 3598;
			ESP.restart();
		}
	#endif
	//add cpat clock
	for (byte i = 0; i < devices_present; i++) {
		if (Settings.pulseon_timer[i] > 0) {
			// must test hour set on , hour set off
			// clock every day (day = 0)
			if (((RtcTime.hour * 60 + RtcTime.minute) == Settings.pulseon_timer[i]) && (bitRead(power, i) == 0)){
				//set on 
				snprintf_P(log_data, sizeof(log_data), "Dev.%d Clock on", i + 1);
				AddLog(LOG_LEVEL_INFO);
				ExecuteCommandPower(i + 1, 1);
			}
			if (((RtcTime.hour * 60 + RtcTime.minute) == Settings.pulse_timer[i]) && (bitRead(power, i) != 0)){
				//set on 
				snprintf_P(log_data, sizeof(log_data), "Dev.%d Clock off", i + 1);
				AddLog(LOG_LEVEL_INFO);
				ExecuteCommandPower(i + 1, 0);
			}
			// clock on a particular day
			if (((RtcTime.day_of_week * 1440 + RtcTime.hour * 60 + RtcTime.minute) == Settings.pulseon_timer[i]) && (bitRead(power, i) == 0)){
				//set on 
				snprintf_P(log_data, sizeof(log_data), "Dev.%d Clock on %d", i + 1, RtcTime.day_of_week);
				AddLog(LOG_LEVEL_INFO);
				ExecuteCommandPower(i + 1, 1);
			}
			if (((RtcTime.day_of_week * 1440 + RtcTime.hour * 60 + RtcTime.minute) == Settings.pulse_timer[i]) && (bitRead(power, i) != 0)){
				//set off
				snprintf_P(log_data, sizeof(log_data), "Dev.%d Clock off %d", i + 1, RtcTime.day_of_week);
				AddLog(LOG_LEVEL_INFO);
				ExecuteCommandPower(i + 1, 0);

			}
		}


	} // end for each device , test clock
	#ifdef USE_SSD1306
		if (WebStarted > 10) {
			OledDis.clear();
		}
	#endif

	#ifdef USE_ADC_MAX // add cpat
		ADCValue(); // extract adc value of A0
		#ifdef USE_SSD1306
			if (WebStarted > 10) {
				OledDis.drawProgressBar(0, 0, 127, 15, Settings.i_max * Settings.i_max_to_off / 1024);
			}// fin web started
		#endif
		if ((Settings.i_max  > Settings.i_max_to_off) && (Settings.i_max_to_off> 30) && (!blink_timer)) {
			//stop all relays on
			boolean j = false;
			for (byte i = 0; i < MAX_RELAYS; i++) {
				if (bitRead(power, i) != 0) {
					ExecuteCommandPower(i + 1, 0);
					j = true;
				}
			}
			if (j) {
				snprintf_P(log_data, sizeof(log_data), "Stop on Current [mA] %d , Maxi %d", Settings.i_max*Settings.ws_red / 10, Settings.i_max_to_off*Settings.ws_red / 10);
				AddLog(LOG_LEVEL_INFO);
			}

		}

	#else
		#ifdef USE_SSD1306
			if (WebStarted > 10) {
				OledDis.drawString(0, 0, F("C.Pat."));
			}// fin web started
		#endif
	#endif
	#ifdef USE_SSD1306

		if (WebStarted > 0) {
			if (WebStarted > 10) {
				char stimer1[4];
				char stimer2[3];
				char stimer3[3];
				char stime[10] = "";
				OledDis.setFont(ArialMT_Plain_10);
				for (byte idx = 1; idx <= devices_present; idx++) {
					if (bitRead(power, idx - 1)) {
						OledDis.fillCircle(8 + 32 * (idx - 1), 24, 7);
					}
					else {
						OledDis.drawCircle(8 + 32 * (idx - 1), 24, 7);
					}
					if (pulse_timer[idx - 1] > 0) {
						snprintf_P(stimer1, sizeof(stimer1), kDecim, ((pulse_timer[idx - 1] > 3700) ? (pulse_timer[idx - 1] - 100) / 3600 : 0));
						snprintf_P(stimer2, sizeof(stimer2), kDecim, ((pulse_timer[idx - 1] > 160) ? ((pulse_timer[idx - 1] - 100) % 3600) / 60 : 0));
						snprintf_P(stimer3, sizeof(stimer3), kDecim, ((pulse_timer[idx - 1] > 110) ? ((pulse_timer[idx - 1] - 100) % 60) : pulse_timer[idx - 1] / 10));
						snprintf_P(stime, sizeof(stime), PSTR("%s:%s:%s"), stimer1, stimer2, stimer3);

						OledDis.drawString(0 + 32 * (idx - 1), 32, stime);

					}
					// modif cpat
					else {
						OledDis.drawString(32 * (idx - 1), 32, GetStateText(bitRead(power, idx - 1)));

					}
				}
				OledDis.setFont(ArialMT_Plain_16);
				//OledDis.drawString(0,32,)
				OledDis.display();
			}
			else {
				WebStarted = WebStarted + 1;
			}
		}

		/*  test for i2cadress
		byte error, address;
		int nDevices;

		Serial.println("Scanning...");

		nDevices = 0;
		for (address = 1; address < 127; address++)
		{
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(address);
		error = Wire.endTransmission();

		if (error == 0)
		{
		Serial.print("I2C device found at address 0x");
		if (address<16)
		Serial.print("0");
		Serial.print(address, HEX);
		Serial.println("  !");

		nDevices++;
		}
		else if (error == 4)
		{
		Serial.print("Unknown error at address 0x");
		if (address<16)
		Serial.print("0");
		Serial.println(address, HEX);
		}
		}
		if (nDevices == 0) {
		Serial.println("No I2C devices found\n");
		}
		else { Serial.println("done\n"); }
		*/
	#endif
}

void newHandleAjaxStatusRefresh()
{
	char svalue[80];
	char stimer1[4];
	char stimer2[3];
	char stimer3[3];
	char stime[10] = "";

	if (strlen(WebServer->arg("o").c_str())) {
		ExecuteCommandPower(atoi(WebServer->arg("o").c_str()), 2);
	}
	if (strlen(WebServer->arg("d").c_str())) {
		snprintf_P(svalue, sizeof(svalue), PSTR(D_CMND_DIMMER " %s"), WebServer->arg("d").c_str());
		ExecuteCommand(svalue);
	}
	if (strlen(WebServer->arg("t").c_str())) {
		snprintf_P(svalue, sizeof(svalue), PSTR(D_CMND_COLORTEMPERATURE " %s"), WebServer->arg("t").c_str());
		ExecuteCommand(svalue);
	}
	if (strlen(WebServer->arg("k").c_str())) {
		snprintf_P(svalue, sizeof(svalue), PSTR(D_CMND_RFKEY "%s"), WebServer->arg("k").c_str());
		ExecuteCommand(svalue);
	}

	String page = "";
	mqtt_data[0] = '\0';
	XsnsCall(FUNC_XSNS_WEB);
	if (strlen(mqtt_data)) {
		page += FPSTR(HTTP_TABLE100);
		page += mqtt_data;
		page += F("</table>");
	}
	char line[80];
	if (devices_present) {
		page += FPSTR(HTTP_TABLE100);
		page += F("<tr>");
		uint8_t fsize = (devices_present < 5) ? 60 - (devices_present * 8) : 32;
		for (byte idx = 1; idx <= devices_present; idx++) {
			snprintf_P(svalue, sizeof(svalue), kDecim, bitRead(power, idx - 1));
			//      snprintf_P(line, sizeof(line), PSTR("<td style='width:%d%'><div style='text-align:center;font-weight:%s;font-size:%dpx'>%s</div></td>"),
			/* nprintf_P(line, sizeof(line), PSTR("<td style='width:%d{t}%s;font-size:%dpx'>%s</div></td>"),  // {t} = %'><div style='text-align:center;font-weight:
			100 / devices_present, (bitRead(power, idx -1)) ? "bold" : "normal", fsize, (devices_present < 5) ? GetStateText(bitRead(power, idx -1)) : svalue);
			*/
			// code cpat add cpat timer pulse as text

#ifdef USE_InterlockDelay
			char color[] = "color:RED;";
			if (!((interlockOff_DeviceOn == idx) && (is_SetToZero))) {
				snprintf_P(color, sizeof(color), PSTR("%s"), "");
			}
#else
			char color[] = "";
#endif
			if (Settings.pulseon_timer[idx - 1] > 0) {
				snprintf_P(line, sizeof(line), PSTR("<td style='width:%d{t}%s;font-size:%dpx;%s'>%s&#169;%s</div></td>"),  // {t} = %'><div style='text-align:center;font-weight:
					100 / devices_present, "bold", (devices_present < 5) ? fsize : fsize / 2, color, GetStateText(bitRead(power, idx - 1)),
					((Settings.Outtimer[idx - 1][0] == '\0') || (bitRead(power, idx - 1) == 0)) ? "" : "!");
			}
			else {
				if (pulse_timer[idx - 1] > 0) {
					snprintf_P(stimer1, sizeof(stimer1), kDecim, ((pulse_timer[idx - 1] > 3700) ? (pulse_timer[idx - 1] - 100) / 3600 : 0));
					snprintf_P(stimer2, sizeof(stimer2), kDecim, ((pulse_timer[idx - 1] > 160) ? ((pulse_timer[idx - 1] - 100) % 3600) / 60 : 0));
					snprintf_P(stimer3, sizeof(stimer3), kDecim, ((pulse_timer[idx - 1] > 110) ? ((pulse_timer[idx - 1] - 100) % 60) : pulse_timer[idx - 1] / 10));
					snprintf_P(stime, sizeof(stime), PSTR("%s:%s:%s"), stimer1, stimer2, stimer3);

					/*snprintf_P(line, sizeof(line), PSTR("<td style='width:%d{t};font-size:%dpx;%s'>%s</div></td>"),  // {t} = %'><div style='text-align:center;font-weight:
					100 / devices_present,  (devices_present < 5) ? fsize  : fsize / 2,color, stime);*/
					snprintf_P(line, sizeof(line), PSTR("<td style='width:%d{t}%s;font-size:%dpx;%s'>%s%s</div></td>"),  // {t} = %'><div style='text-align:center;font-weight:
						100 / devices_present, "bold", (devices_present < 5) ? fsize * 2 / 3 : fsize / 2, color, stime,
						((Settings.Outtimer[idx - 1][0] == '\0') || (bitRead(power, idx - 1) == 0)) ? "" : "!");
				}
				// modif cpat
				else {
					/*
					snprintf_P(line, sizeof(line), PSTR("<td style='width:%d{t}%s;font-size:%dpx;%s'>%s</div></td>"),  // {t} = %'><div style='text-align:center;font-weight:
					100 / devices_present, (bitRead(power, idx - 1)) ? F("bold") : F("normal"), (devices_present < 5) ? fsize : fsize / 2, color,GetStateText(bitRead(power, idx - 1)));
					*/
					snprintf_P(line, sizeof(line), PSTR("<td style='width:%d{t}%s;font-size:%dpx;%s'>%s%s</div></td>"),  // {t} = %'><div style='text-align:center;font-weight:
						100 / devices_present, "bold", (devices_present < 5) ? fsize : fsize / 2, color, GetStateText(bitRead(power, idx - 1)),
						((Settings.Outtimer[idx - 1][0] == '\0') || (bitRead(power, idx - 1) == 0)) ? "" : "!");
				}
			}
			/* old code
			if (pulse_timer[idx-1]>0) {
			snprintf_P(stimer1, sizeof(stimer1), PSTR("%d"), ((pulse_timer[idx - 1] > 3700) ? (pulse_timer[idx - 1] - 100) / 3600 : 0));
			snprintf_P(stimer2, sizeof(stimer2), PSTR("%d"), ((pulse_timer[idx - 1] > 160) ? ((pulse_timer[idx - 1] - 100) % 3600) / 60 : 0));
			snprintf_P(stimer3, sizeof(stimer3), PSTR("%d"), ((pulse_timer[idx - 1]>110) ? ((pulse_timer[idx - 1] - 100) % 60) : pulse_timer[idx - 1] / 10));
			snprintf_P(stime, sizeof(stime), PSTR("%s:%s:%s"), stimer1, stimer2, stimer3);

			snprintf_P(line, sizeof(line), PSTR("<td style='width:%d{t}%s;font-size:%dpx'>%s</div></td>"),  // {t} = %'><div style='text-align:center;font-weight:
			100 / devices_present, "normal", (devices_present < 5) ? fsize/2 : fsize / 3,  svalue);


			}
			else {
			snprintf_P(line, sizeof(line), PSTR("<td style='width:%d{t}%s;font-size:%dpx'>%s</div></td>"),  // {t} = %'><div style='text-align:center;font-weight:
			100 / devices_present, (bitRead(power, idx - 1)) ? "bold" : "normal", (devices_present < 5) ? fsize : fsize/2 ,  GetStateText(bitRead(power, idx - 1)) );
			}
			*/
			page += line;
		}
		page += F("</tr></table>");
	}
	/*
	* Will interrupt user action when selected
	if (light_type) {
	snprintf_P(line, sizeof(line), PSTR("<input type='range' min='1' max='100' value='%d' onchange='lb(value)'>"),
	Settings.light_dimmer);
	page += line;
	}
	*/
	WebServer->send(200, FPSTR(HDR_CTYPE_HTML), page);
} // not use yet
#ifdef Use_Relay
	

#endif


#ifdef Use_Relay

#endif
#ifdef USE_ADC_MAX  // add cpat
	void ADCValue() {
		// user to read every 0.2 seconds stateloop the adc max current value (alternative current 1 p?riode)
		uint8_t analog = 0;
		uint8_t readAdc = 0;
		if (GPIO_ADC0 < 99) {
			for (byte i = 0; i < 32; i++) {
				readAdc = analogRead(A0);
				if (readAdc > analog) {
					analog = readAdc;
				}
				delayMicroseconds(625);  // 50 Hz p?riode = 20 ms/ 32
			}
		}
		Settings.i_max = analog;
	} // end ADCValue
#endif

