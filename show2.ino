void showtime(){
//timeClient.update();
//Serial.println(timeClient.getFormattedTime());
   Serial.println(Austria.dateTime("H:i:s"));

    matrix.fillScreen(0);
    matrix.setCursor(0, 0);
    matrix.setTextColor( matrix.Color(0 + Austria.second(), 255 - Austria.second(), 10 + 4* Austria.minute()) );
  
    matrix.print(Austria.dateTime("H");
    matrix.setCursor(0+6+1+6+2,0);
  
    matrix.print(Austria.dateTime("i");
    //matrix.setTextColor( matrix.Color(0, 255, 0) );
    matrix.drawLine(14,0,14,9,matrix.Color(50,50,50));
  
    matrix.show();
    
    if (minuteChanged()) {
	for (int i=0; i <= 8, ++i){   
		matrix.drawFastHLine(0,i,32,matrix.Color(10+i*7,10+i*7,127));
		delay(50);
   	}
    delay(500);
    }

}

void showweather(){
   int h, y;
   h = 0;
   Serial.println("Wetter");
 /*  for (y=0; y<matrix.Height(); ++y)
    {
      matrix.DrawLine(0, y, matrix.Width() - 1, y, CHSV(h, 255, 255));
      h+=16;
    }
    delay(1000); */
    matrix.fillScreen(0);
    matrix.setCursor(0, 0);
    matrix.print(F("20:59"));
    matrix.setTextColor( matrix.Color(0, 255, 0) );
  
    matrix.show();
}
