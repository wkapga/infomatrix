void showtime(){
//timeClient.update();
//Serial.println(timeClient.getFormattedTime());
   Serial.println(Austria.dateTime("H:i:s"));

    matrix.fillScreen(0);
    matrix.setCursor(0, 0);
    matrix.setTextColor( matrix.Color(0 + 3* Austria.second(), 255 - 3* Austria.second(), 10 + 4* Austria.minute()) );
  
    matrix.print(Austria.dateTime("H"));
    matrix.setCursor(0+5+1+5+2,0);
  
    matrix.print(Austria.dateTime("i"));
    //matrix.setTextColor( matrix.Color(0, 255, 0) );
    matrix.drawLine(12,0,12,8,matrix.Color(150,150,50));
  
    matrix.show();
    
    // if (minuteChanged()) {
	   if (Austria.second()==0 ) {
	    for (int i=0; i <= 8, i++;){   
		  matrix.drawFastHLine(0,i,32,matrix.Color(10+i*7,10+i*7,127));
      matrix.show();
		  delay(500);
   	  }
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
