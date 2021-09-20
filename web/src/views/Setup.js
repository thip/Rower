import { useState } from 'react';
import Entry from '../components/Entry';

function Setup(props) {
  const [time, setTime] = useState(0);
  const [distance, setDistance] = useState(0);

  const updateTime = (value) => setTime(value > 0 ? value : 0);
  const updateDistance = (value) => setDistance(value > 0 ? value : 0);

  const onStart = () => props.onStart({distance, time: time*60*1000});

  return (
      <div style={{display: "flex", alignSelf: "center", height: "500px"}}>
        <div style={{display: "flex", flexDirection: "column", justifyContent: "space-between"}}>
          <Entry values={[1000,200,50]} value={distance} onChange={updateDistance} format={value => `${value.toLocaleString()}m`}/>
          <Entry values={[20,5,1]} value={time} onChange={updateTime} format={value => `${value} minutes`}/>
          <div style={{ textAlign: "center", margin: "15px", fontSize: "70px"}}>
            {pace(distance, time)}/500m
          </div>
        </div>
        <div style={{margin: "15px"}}>
          <button style={{width: "200px"}} onClick={onStart}>Start</button>
        </div>
      </div>
  );
}

function pace(distance, time){
  
  if (distance === 0 || time === 0) {
    return "-"
  }

  const velocity = distance/(time*60);

  const pace = Math.round(500/velocity);

  const minutes = Math.floor(pace / 60);
  const seconds = Math.round(pace - minutes * 60);

  return `${minutes}:${seconds < 10 ? "0" : ""}${seconds}`
}

export default Setup;
