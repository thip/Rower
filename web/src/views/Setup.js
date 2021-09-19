import { useState } from 'react';
import TimeEntry from '../components/Entry';

function Setup(props) {
  const [time, setTime] = useState(0);
  const [distance, setDistance] = useState(0);

  const updateTime = (value) => setTime(value > 0 ? value : 0);
  const updateDistance = (value) => setDistance(value > 0 ? value : 0);

  const onStart = () => props.onStart({distance, time});

  return (
      <div style={{display: "flex", alignSelf: "center", height: "800px"}}>
        <div style={{display: "flex", flexDirection: "column", justifyContent: "space-between"}}>
          <TimeEntry values={[20,5,1]} value={time} onChange={updateTime} format={value => `${value} minutes`}/>
          <TimeEntry values={[1000,200,50]} value={distance} onChange={updateDistance} format={value => `${value.toLocaleString()}m`}/>
          <div style={{ textAlign: "center", margin: "25px", fontSize: "100px"}}>
            {pace(distance, time)}
          </div>
        </div>
        <div style={{margin: "20px"}}>
          <button style={{width: "300px"}} onClick={onStart}>Start</button>
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

  return `${minutes}:${seconds < 10 ? "0" : ""}${seconds}/500m`
}

export default Setup;
