import React, { Component } from "react";
import logo from "./logo.svg";
import "./App.css";
import { CircleSlider } from "react-circle-slider";
import { RemoveScroll } from "react-remove-scroll";

import JTimepicker from "reactjs-timepicker";

class App extends Component {
  constructor(props) {
    super(props);
    this.state = { value1: 0, value2: 0,
                   time1: "00:00", time2: "00:00" };
  }

  handleChange1 = value1 => {
    fetch("/led1", { method: "PUT", body: value1 })
      .then(response => response.text())
      .then(this.setState({ value1 }));
  };

  handleChange2 = value2 => {
    fetch("/led2", { method: "PUT", body: value2 })
      .then(response => response.text())
      .then(this.setState({ value2 }));
  };

  /*handleChangeRange = event => {
    this.setState({
      value1: event.target.valueAsNumber,
      value2: event.target.valueAsNumber
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
                value={this.state.value1}
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
                value={this.state.value4}
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
                onChange={this.handleChangeTime1} 
                color="#072c07"
                inputVisible={true} 
              />
              <h1 className="App-title">Final</h1>
              <JTimepicker 
                value={this.state.time}
                onChange={this.handleChangeTime2} 
                color="#072c07" 
                inputVisible={true}
                style={{ size: 50 }}
              />
            </RemoveScroll>
          </section>
        </header>
      </div>
    );
  }
}

export default App;
