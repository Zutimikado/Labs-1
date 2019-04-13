var xhr = new XMLHttpRequest();
xhr.open("GET", 'https://api.openweathermap.org/data/2.5/weather?q=Minsk&appid=d3035b1339c54a24bef66cb08652ac63', true);
xhr.send(null);
 
xhr.onreadystatechange=function(){
  if (xhr.readyState !== 4) return;
  if (xhr.status === 200) {
     alert(xhr.responseText);
  }
}