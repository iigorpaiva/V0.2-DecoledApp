import React, { Component } from "react";
import logo from "./logo.svg";
import "./App.css";
import { CircleSlider } from "react-circle-slider";
import { RemoveScroll } from "react-remove-scroll";
import ToggleButton from "react-toggle-button";
import ScheduleSelector from "react-schedule-selector";
import { layoutGenerator } from "react-break";

class App extends Component {
  constructor(props) {
    super(props);
    this.state = { led1: 0, led2: 0, ledC: 0, schedule: [],
                   ledon1: false, ledon2: false };
  }

  componentDidMount() {
    Promise.all([
      fetch("/led1"),
      fetch("/led2"),
      fetch("/ledC"),
      fetch("/control"),
    ])
      .then(([res1, res2, res3, res4 ]) =>
        Promise.all([res1.text(), res2.text(), res3.text(), res4.json()])
      )
      .then(([led1, led2, ledC, schedule]) =>
        this.setState({ led1, led2, ledC, schedule})
      );

    fetch("/ledon1")
      .then(response => response.text())
      .then(state => this.setledstate1(state));
    fetch("/ledon2")
      .then(response => response.text())
      .then(state => this.setledstate2(state));
  }

  //------------------------- INTENSIDADE -------------------------------------------

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

  //------------------------- INTENSIDADE CONTROLE ----------------------------------

  handleChangeControl = ledC => {
    fetch("/ledC", { method: "PUT", body: ledC })
      .then(response => response.text())
      .then(this.setState({ ledC }));
  };
  
  //------------------------- INTERVALOS CONTROLE  ----------------------------------

  handleChange = newSchedule => {
    const horarios = JSON.stringify(newSchedule);

    fetch("/control", { method: "PUT", body: horarios })
      .then(response => response.json())
      .then(this.setState({ schedule: newSchedule }));

    //console.log("meu json eh: ", horarios);
  };

  // ------------------------- TOGGLES ----------------------------------------------

  handleStateChange1(ledon1) {
    fetch("/ledon1", { method: "PUT", body: ledon1 ? "0" : "1" })
      .then(response => response.text())
      .then(state => this.setledstate1(state))
  }

  handleStateChange2(ledon2) {
    fetch("/ledon2", { method: "PUT", body: ledon2 ? "0" : "1" })
      .then(response => response.text())
      .then(state => this.setledstate2(state));
  }

  setledstate1(state) {
    this.setState({ ledon1: state !== "0" });
  }

  setledstate2(state) {
    this.setState({ ledon2: state !== "0" });
  }


  //------------------------- RENDER --------------------------------------------------

  render() {
    const layout = layoutGenerator({
      mobile: 0,
      phablet: 550,
      tablet: 768,
      desktop: 992
    });

  //------------------------- VERIFICA SE EH CELULAR, DESKTOP, TABLET -----------------

    const OnMobile = layout.is("mobile");
    const OnAtLeastTablet = layout.isAtLeast("tablet");
    const OnAtMostPhablet = layout.isAtMost("phablet");
    const OnDesktop = layout.is("desktop");

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
              <div className="Direita">
                <ToggleButton
                  value={this.state.ledon1}
                  onToggle={value => this.handleStateChange1(value)}
                />
              </div>
            </RemoveScroll>
          </section>
          <section class="App-trans" id="hall">
            <img src={logo} className="App-logo" alt="logo" />
            <h1 className="App-title">Hall</h1>
            <RemoveScroll>
              <CircleSlider
                onChange={this.handleChange2}
                value={this.state.led2}
                size={150}
                showTooltip={true}
                gradientColorFrom="#009f5c"
                gradientColorTo="#006b5c"
                showPercentage={true}
                tooltipColor="#6ab6e1"
                stepSize={20}
              />
              <div className="Direita">
                <ToggleButton
                  value={this.state.ledon2}
                  onToggle={value => this.handleStateChange2(value)}
                />
            </div>
            </RemoveScroll>
          </section>
          <section class="App-trans" id="controle">
            <OnDesktop>
              <ScheduleSelector
                selection={this.state.schedule}
                numDays={20}
                minTime={8}
                maxTime={17}
                onChange={this.handleChange}
                selectedColor="#14a806"
                margin={2}
              />
            </OnDesktop>
            <OnMobile>
              <img src={logo} className="App-logo" alt="logo" />
              <h1 className="App-title">Controle</h1>
            </OnMobile>
            <CircleSlider
              onChange={this.handleChangeControl}
              value={this.state.ledC}
              size={150}
              showTooltip={true}
              gradientColorFrom="#009f5c"
              gradientColorTo="#006b5c"
              showPercentage={true}
              tooltipColor="#6ab6e1"
              stepSize={20}
            />
          </section>
        </header>
      </div>
    );
  }
}

export default App;
