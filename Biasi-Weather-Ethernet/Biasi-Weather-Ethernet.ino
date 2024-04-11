// Send HTML content to the client to display the sensor data on a web page
client.print("<h1 style='color: orange;'>Temperature I: ");
client.print(t1);
client.print(" *C</h1>");

client.print("<h1 style='color: orange;'>Temperature II: ");
client.print(t2);
client.print(" *C</h1>");

client.print("<h1 style='color: red;'>Temperature AVG: ");
client.print(tavg);
client.print(" *C</h1>");

client.print("<h1 style='color: blue;'>Humidity: ");
client.print(h);
client.print(" %</h1>");

client.print("<h1 style='color: green;'>Pressure: ");
client.print(p);
client.print(" mBar</h1>");

client.println("</body>");
client.println("</html>");
// Break out of
