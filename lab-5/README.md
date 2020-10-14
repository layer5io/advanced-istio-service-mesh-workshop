# Lab 5 - Traffic management with a service mesh

If you haven't forked or cloned this repository, please do so now:

```
git clone https://github.com/layer5io/advanced-istio-service-mesh-workshop
```

## 5.1 Start managing traffic routes

Some basics to get us started.

## 5.1.1 Send all requests to Productpage v1

```yaml
apiVersion: networking.istio.io/v1alpha3
kind: VirtualService
metadata:
  name: reviews
spec:
  hosts:
    - reviews
  http:
    - route:
        - destination:
            host: reviews
            subset: v1
```

_Using Meshery, apply custom configuration._

## 5.1.2 Send all requests to Productpage 2

```yaml
apiVersion: networking.istio.io/v1alpha3
kind: VirtualService
metadata:
  name: reviews
spec:
  hosts:
    - reviews
  http:
    - route:
        - destination:
            host: reviews
            subset: v2
```

_Using Meshery, apply custom configuration._

1. cd into the `route-v1-v2` directory.

## 5.2

1. cd into the `route-header` directory.

**Generate Load on Bookinfo**
See [Lab 4](../lab-4/README.md] for instructions for running a performance test.

<h2>
  <a href="../lab-6/README.md">
  <img src="../img/go.svg" width="32" height="32" align="left" />
  Continue to Lab 6</a>: Exploring security capabilities in Istio
</h2>

<br />
<hr />

Alternative, manual installation steps are provided for reference below. No need to execute these if you have performed the steps above.

<hr />
