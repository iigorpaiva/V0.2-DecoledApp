import React, { Component } from "react";
import logo from "./logo.svg";
import "./App.css";
import { CircleSlider } from "react-circle-slider";
import { RemoveScroll } from "react-remove-scroll";

import JTimepicker from "reactjs-timepicker";

class App extends Component {
  constructor(props) {
    super(props);
    this.state = { led1: 0, led2: 0, time1: "00:00", time2: "00:00"};
  }

  componentDidMount(){
    Promise.all([
        fetch('/led1'),
        fetch('/led2'),
        fetch('/time1'),
        fetch('/time2')
    ])
    .then(([res1, res2, res3, res4]) => Promise.all([res1.text(), res2.text(), res3.text(), res4.text()]))
    .then(([led1, led2, time1, time2]) => this.setState({led1, led2, time1, time2}))
  }

  handleChange1 = led1 => {
    fetch("/led1", { method: "PUT", body: led1 })
      .then(response => response.text())
      .then(this.setState({ led1 }));
  };

  handleChange2 = led2 => {
    fetch("/led2", { method: "PUT", body: led2 })
      .then(response => response.text())
      .then(this.setState({ led2 }));
  };

  /*handleChangeRange = event => {
    this.setState({
      led1: event.target.valueAsNumber,
      led2: event.target.valueAsNumber
    });
  };*/

  handleChangeTime1 = time1 => {
    fetch("/time1", { method: "PUT", body: time1 })
      .then(response => response.text())
      .then(this.setState({ time1 }))
      .then(console.log(time1));
  };

  handleChangeTime2 = time2 => {
    fetch("/time2", { method: "PUT", body: time2 })
      .then(response => response.text())
      .then(this.setState({ time2 }))
      .then(console.log(time2));
  };

  render() {
    return (
      <div className="App">
        <header className="App-header">
          <body data-spy="scroll" data-target="#lambda-navbar" data-offset="0">
            <nav
              class="navbar navbar-expand-md navbar-dark navbar-transparent fixed-top sticky-navigation"
              id="lambda-navbar"
            >
              <a class="navbar-brand" href="">
                Decoled App
              </a>
              <button
                class="navbar-toggler navbar-toggler-right border-0"
                type="button"
                data-toggle="collapse"
                data-target="#navbarCollapse"
                aria-controls="navbarCollapse"
                aria-expanded="false"
                aria-label="Toggle navigation"
              >
                <span data-feather="menu"></span>
              </button>
              <div class="collapse navbar-collapse" id="navbarCollapse">
                <ul class="navbar-nav ml-auto">
                  <li class="nav-item">
                    <a class="nav-link page-scroll" href="#principal">
                      Sala
                    </a>
                  </li>
                  <li class="nav-item">
                    <a class="nav-link page-scroll" href="#hall">
                      Hall
                    </a>
                  </li>
                  <li class="nav-item">
                    <a class="nav-link page-scroll" href="#controle">
                      Controle
                    </a>
                  </li>
                </ul>
              </div>
            </nav>
          </body>

          <section class="App-trans" id="principal">
            <img src={logo} className="App-logo" alt="logo" />
            <h1 className="App-title">Sala</h1>
            <RemoveScroll>
              <CircleSlider
                onChange={this.handleChange1}
                value={this.state.led1}
                size={150}
                showTooltip={true}
                gradientColorFrom="#009f5c"
                gradientColorTo="#006b5c"
                showPercentage={true}
                tooltipColor="#6ab6e1"
                stepSize={20}
              />
            </RemoveScroll>
          </section>
          <section class="App-trans" id="hall">
            <img src={logo} className="App-logo" alt="logo" />
            <h1 className="App-title">Hall</h1>
            <RemoveScroll>
              <CircleSlider
                onChange={this.handleChange2}
                value={this.state.led2}
                size={140}
                showTooltip={true}
                gradientColorFrom="#009f5c"
                gradientColorTo="#006b5c"
                showPercentage={true}
                tooltipColor="#6ab6e1"
                stepSize={20}
              />
            </RemoveScroll>
          </section>
          <section class="App-trans" id="controle">
            <RemoveScroll>
              <h1 className="App-title">Início</h1>
              <JTimepicker
                defaultTime={this.state.time1}
                onChange={this.handleChangeTime1.bind(this)}
                color="#072c07"
                inputVisible={true}
              />
              <h1 className="App-title">Final</h1>
              <JTimepicker
                defaultTime={this.state.time2}
                onChange={this.handleChangeTime2.bind(this)}
                color="#072c07"
                inputVisible={true}
              />
            </RemoveScroll>
          </section>
        </header>
      </div>
    );
  }
}

export default App;
