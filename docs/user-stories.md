# User Stories — Smart Springfield

## Epic: Device Monitoring & Management

### US-001

**Title:** View real-time sensor data  
**Priority:** High  
**User Story:**  
As a city operator, I want to view real-time sensor data (e.g., air quality,
traffic, waste levels) so that I can monitor city conditions.

**Acceptance Criteria:**

- Dashboard shows live data updates
- Data is grouped per sensor type/location
- Refresh interval ≤ 5 seconds

---

### US-002

**Title:** View device status  
**Priority:** High  
**User Story:**  
As a city operator, I want to see the status of all connected devices so that I
can detect failures quickly.

**Acceptance Criteria:**

- Devices show online/offline status
- Last seen timestamp is visible
- Status updates automatically

---

### US-003

**Title:** Filter devices by location/type  
**Priority:** Medium  
**User Story:**  
As a city operator, I want to filter devices by location or type so that I can
focus on relevant infrastructure.

**Acceptance Criteria:**

- Filters available for location and device type
- Filtering updates results instantly

---

## Epic: Alerts & Notifications

### US-004

**Title:** Receive alerts for threshold breaches  
**Priority:** High  
**User Story:**  
As a city operator, I want to receive alerts when sensor values exceed
thresholds so that I can respond quickly.

**Acceptance Criteria:**

- Alerts triggered based on configurable thresholds
- Alerts have priority levels (warning, critical)
- Alert message includes sensor, value, and location

---

### US-005

**Title:** View alert history  
**Priority:** Medium  
**User Story:**  
As a city operator, I want to view past alerts so that I can analyze incidents.

**Acceptance Criteria:**

- Alerts are stored and retrievable
- Filter by date, type, severity

---

## Epic: Automation & Control

### US-006

**Title:** Trigger actuator actions automatically  
**Priority:** High  
**User Story:**  
As a city operator, I want the system to automatically trigger actions (e.g.,
lights, fans) when conditions are met so that manual intervention is reduced.

**Acceptance Criteria:**

- Rules can be configured (if X then Y)
- Actions execute within seconds
- Actions are logged

---

### US-007

**Title:** Manually control actuators  
**Priority:** Medium  
**User Story:**  
As a city operator, I want to manually control actuators so that I can override
automation when needed.

**Acceptance Criteria:**

- UI allows sending commands (on/off/etc.)
- Feedback from actuator is displayed

---

## Epic: Data Visualization

### US-008

**Title:** View historical sensor data  
**Priority:** Medium  
**User Story:**  
As a city operator, I want to view historical data trends so that I can analyze
patterns over time.

**Acceptance Criteria:**

- Graphs display data over selectable time ranges
- Multiple sensors can be compared

---

### US-009

**Title:** Dashboard overview  
**Priority:** High  
**User Story:**  
As a city operator, I want a dashboard overview of key metrics so that I can
quickly assess city status.

**Acceptance Criteria:**

- Summary widgets (avg values, alerts, device count)
- Visual indicators for critical states

---

## Epic: System Monitoring

### US-010

**Title:** Monitor system health  
**Priority:** High  
**User Story:**  
As a city operator, I want to monitor system health (broker/API availability) so
that I can ensure system reliability.

**Acceptance Criteria:**

- Status of services is visible
- Downtime events are logged

---

### US-011

**Title:** Detect sensor inactivity  
**Priority:** Medium  
**User Story:**  
As a city operator, I want to detect when sensors stop sending data so that I
can investigate issues.

**Acceptance Criteria:**

- Alert triggered if no data within defined interval
- Affected sensor is highlighted

---

## Epic: Data Access & Interaction

### US-012

**Title:** View sensor details  
**Priority:** Low  
**User Story:**  
As a city operator, I want to view detailed information about a sensor so that I
understand its configuration and data.

**Acceptance Criteria:**

- Shows metadata (ID, type, location)
- Shows recent readings

---

### US-013

**Title:** Export data  
**Priority:** Low  
**User Story:**  
As a city operator, I want to export sensor data so that I can use it for
external analysis.

**Acceptance Criteria:**

- Export available in CSV/JSON
- User can select time range
