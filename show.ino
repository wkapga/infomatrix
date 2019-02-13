void showtime(){
//timeClient.update();
//Serial.println(timeClient.getFormattedTime());
   Serial.println(Austria.dateTime("H:i:s"));
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
