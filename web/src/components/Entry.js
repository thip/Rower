import Changer from "./Changer";

function Entry(props){
    const incriment = (amount) => {
        return () => {
            const  newValue = props.value+amount;
            props.onChange(newValue);
        }
    }

    return(
        <div style={{ display: "flex", height: "200px"}}>
            <div style={{ alignSelf: "center", textAlign: "center", width: "350px", fontSize:"64px", margin: "15px"}}>
                {props.format(props.value)}
            </div>

            <div style={{ display: "flex", margin: "15px"}}>
                {
                    props.values.map(value => <Changer up={`+${value}`} down={`-${value}`} onUp={incriment(value)} onDown={incriment(-value)} key={value}/>)
                }
            </div>
        </div>
    )
}

export default Entry;