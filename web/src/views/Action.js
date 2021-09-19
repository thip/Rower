import { useState } from 'react';

function Action() {
  const [time, setTime] = useState(0);
  const [distance, setDistance] = useState(0);

  const updateTime = (value) => setTime(value > 0 ? value : 0);
  const updateDistance = (value) => setDistance(value > 0 ? value : 0);

  return (
    <div style={{display: "flex", alignSelf: "center", height: "800px"}}>
      Hello
    </div>
  );
}

export default Action;
