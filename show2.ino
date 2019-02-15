void showtime(){
   //Serial.println(Austria.dateTime("H:i:s"));
    int cc; // current clock color
    int hr, sec;
    sec = Austria.second();
    hr =  Austria.hour();

    cc =   matrix.Color(3 * sec + 3 * hr,
			255 - 3 * sec + 3 * hr, 
			255 - 2 * hr) ;
    matrix.fillScreen(0);
    matrix.setTextColor(cc);

    if (Austria.hour()>10) {  
        matrix.setCursor(0, 0);
    	matrix.print(Austria.dateTime("H"));
    } else {
	matrix.setCursor(6,0);
    	matrix.print(Austria.dateTime("G"));
    } 
 
    matrix.setCursor(14,0);
  
    matrix.print(Austria.dateTime("i"));
    //matrix.setTextColor( matrix.Color(0, 255, 0) );
    matrix.drawLine(12,2,12,6,cc));
  
    matrix.show();
    
    // if (minuteChanged()) {
    if (Austria.second()==0 ) {
	for (int i=0; i <= 7, i++;){   
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
