import { useEffect, useState } from 'react';


function Slider(props) {
  const progress = props.progress > 1 ? 1 : props.progress;
  return (
    <div style={{width: `${props.width}px`, height: "20px", background: props.background, overflow: "hidden", margin: "15px"}}>
      <div style={{marginLeft: `${progress*(props.width-20)}px`, width: "20px", height: "100%", background: props.color}}>🚣</div>
    </div>
  )
}

function Action(props) {
  const [time, setTime] = useState(0);
  const [distance, setDistance] = useState(0);
  const [velocity, setVelocity] = useState(0);

  useEffect(() => {
    const interval = setInterval(() => {
      setTime(Date.now() - props.startTime);
      fetch('http://rower.local/data')
        .then(response => response.json())
        .then(data => {
          setDistance(data.distance);
          setVelocity(data.velocity)
        });

    }, 250);
    return () => clearInterval(interval);
  }, [setTime, setDistance, setVelocity, props.startTime]);


  return (
    <div style={{display: "flex", flexDirection: "column", alignSelf: "center", height: "600px"}}>
      <div>{formatTime(time)}</div>
      <div>{distance}m</div>

      <Slider width={800} progress={targetDistance(time, props.targetTime, props.targetDistance)/props.targetDistance} background="lightblue" color="red" />
      <Slider width={800} progress={distance/props.targetDistance} background="lightblue" color="green" />
    </div>
  );
}


function targetDistance(time, targetTime, distance){
  const velocity = distance/targetTime;
  return time * velocity;
}

function formatTime(millis){
  const time = millis/1000

  const minutes = Math.floor(time / 60);
  const seconds = Math.round(time - minutes * 60);

  return`${minutes}:${seconds < 10 ? "0" : ""}${seconds}`;
}

export default Action;
